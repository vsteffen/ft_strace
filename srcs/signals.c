#include "ft_strace.h"

const char		*si_code_to_str(siginfo_t *si)
{
	static const struct s_si_code si_code[] = {
	#include "signals/si_code.h"
	};
	static const struct s_si_code_regular si_code_reg[] = {
	#include "signals/si_code_reg.h"
	};

	if (si->si_code == SI_KERNEL)
		return ("SI_KERNEL");
	if (si->si_code <= 0)
	{
		for (uint8_t i = 0; i < COUNT_OF(si_code_reg); i++)
		{
			if (si->si_code == si_code_reg[i].si_code)
				return (si_code_reg[i].to_str);
		}
		return (SI_CODE_UNKNWON_TO_STR);
	}
	for (uint8_t i = 0; i < COUNT_OF(si_code); i++)
	{
		if (si->si_signo == si_code[i].si_signo)
		{
			for (; i < COUNT_OF(si_code); i++)
			{
				if (si->si_code == si_code[i].si_code)
					return (si_code[i].to_str);
				if (si->si_signo != si_code[i].si_signo)
					return (SI_CODE_UNKNWON_TO_STR);
			}

		}
	}
	return (SI_CODE_UNKNWON_TO_STR);
}

const char		*si_signo_to_str(siginfo_t *si)
{
	static const char *si_signo[] = {
	#include "signals/si_signo.h"
	};

	return (si_signo[si->si_signo]);
}

void		print_sig(pid_t child, enum e_si_life si_life)
{
	siginfo_t			si;
	static const char	*last_si_name = NULL;

	if (ptrace(PTRACE_GETSIGINFO, child, NULL, &si) == -1 && si_life == SI_ALIVE)
		die("ptrace", child);
	if (si_life == SI_ALIVE) {
		last_si_name = si_signo_to_str(&si);
		dprintf(STDERR_FILENO, "--- %s {si_signo=%s, si_code=%s, si_pid=%d, si_uid=%u, si_status=%d, si_utime=%ld, si_stime=%ld} ---\n",
			last_si_name, si_signo_to_str(&si), si_code_to_str(&si), si.si_pid, si.si_uid, si.si_status, si.si_utime, si.si_stime);
	}
	else
		dprintf(2, "+++ killed by %s +++\n", last_si_name);
}

void		wait_and_block_signals(pid_t child, int *status) {
	sigset_t	sig_new_mask;
	sigset_t	sig_block;

	if (sigemptyset(&sig_new_mask) == -1 || sigemptyset(&sig_block))
		die("sigemptyset", child);
	if (sigprocmask(SIG_SETMASK, &sig_new_mask, NULL) == -1)
		die("sigprocmask", child);
	if (waitpid(child, status, 0) == -1)
		die("waitpid", child);
	if (sigaddset(&sig_block, SIGHUP) == -1 || sigaddset(&sig_block, SIGINT) == -1 || sigaddset(&sig_block, SIGQUIT) == -1 \
		|| sigaddset(&sig_block, SIGPIPE) == -1  || sigaddset(&sig_block, SIGTERM) == -1)
		die("sigaddset", child);
	if (sigprocmask(SIG_BLOCK, &sig_block, NULL) == -1)
		die("sigprocmask", child);
}

bool		handle_sig_and_wait_syscall(pid_t child, enum e_si_life si_life)
{
	static int status;

	if (si_life == SI_DEAD) {
		if (WIFSIGNALED(status))
			print_sig(child, SI_DEAD);
		else
			dprintf(STDERR_FILENO, "+++ exited with %d +++\n", WEXITSTATUS(status));
		return (true);
	}

	bool signal_inj = false;
	while (42) {
		if (signal_inj) {
			if (ptrace(PTRACE_SYSCALL, child, 0, WSTOPSIG(status)) == -1)
				die("ptrace", child);
			signal_inj = false;
		}
		else {
			if (ptrace(PTRACE_SYSCALL, child, 0, 0) == -1)
				die("ptrace", child);
		}

		wait_and_block_signals(child, &status);

		if (WIFEXITED(status))
			return (false);
		else if (WIFSIGNALED(status))
			return (false);
		else if (WIFSTOPPED(status)) {
			if (WSTOPSIG(status) & 0x80)
				return (true);
			else
				print_sig(child, SI_ALIVE);
			signal_inj = true;
		}
	}
}
