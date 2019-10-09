#include "ft_strace.h"

void		tracee(char *bin, char **av_bin, char **env)
{
	int		status;

	kill(getpid(), SIGSTOP);
	if ((status = execve(bin, av_bin, env)) == -1) {
		dprintf(STDERR_FILENO, "ft_strace: exec: %s\n", strerror(errno));
		exit(status);
	}
	exit(0);
}

static inline void die(char *fn_fail, pid_t child) {
	dprintf(STDERR_FILENO, "ft_strace: ");
	perror(fn_fail);
	kill(child, SIGKILL);
    exit(EXIT_FAILURE);
}

const char		*si_code_to_str(siginfo_t *si)
{
	static const struct s_si_code si_code[] = {
	#include "si_code.h"
	};
	static const struct s_si_code_regular si_code_reg[] = {
	#include "si_code_reg.h"
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
	#include "si_signo.h"
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

enum e_syscall_arch	get_syscall_arch(pid_t child, struct iovec *io)
{
	#ifdef __x86_64__
		static bool first_time = true;
	#endif

	if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, io))
		die("ptrace", child);

	if (io->iov_len == sizeof(struct i386_user_regs_struct)) {
		#ifdef __x86_64__
			if (first_time) {
				first_time = false;
				dprintf(STDERR_FILENO, "ft_strace: [ Process PID=%d runs in 32 bit mode. ]\n", child);
			}
		#endif
		return SYSCALL_32;
	}
	else {
		return SYSCALL_64;
	}
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

void		initialize_tracer(pid_t child, int *status) {
	if (ptrace(PTRACE_SEIZE, child, NULL, NULL) == -1)
		die("ptrace", child);
	wait_and_block_signals(child, status);
	if (ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD)) //| PTRACE_O_TRACEEXEC | PTRACE_O_TRACEEXIT))
		die("ptrace", child);
}

void		get_registers_values(union x86_64_regs *regs, int child) {
	if (ptrace(PTRACE_GETREGS, child, NULL, regs) == -1)
		die("ptrace", child);
}

bool		handle_sig_and_wait_syscall(pid_t child, int *status)
{
	bool signal_inj = false;

	while (42) {
		if (signal_inj) {
			if (ptrace(PTRACE_SYSCALL, child, 0, WSTOPSIG(*status)) == -1)
				die("ptrace", child);
			signal_inj = false;
		}
		else {
			if (ptrace(PTRACE_SYSCALL, child, 0, 0) == -1)
				die("ptrace", child);
		}

		wait_and_block_signals(child, status);
		if (WIFEXITED(*status)) {
			return (false);
		}
		else if (WIFSIGNALED(*status)) {
			print_sig(child, SI_DEAD);
			exit(0);
		}
		else if (WIFSTOPPED(*status)) {
			if (WSTOPSIG(*status) & 0x80)
				return (true);
			else
				print_sig(child, SI_ALIVE);
			signal_inj = true;
		}
	}
}

void		tracer(pid_t child)
{
	enum e_syscall_arch syscall_arch;
	union x86_64_regs regs;
	struct iovec io = {
		.iov_base = &regs,
		.iov_len = sizeof(regs)
	};
	int		status;

	initialize_tracer(child, &status);
	while(42)
	{
		if (!handle_sig_and_wait_syscall(child, &status))
			break;
		get_registers_values(&regs, child);
		syscall_arch = get_syscall_arch(child, &io);
		if (syscall_arch == SYSCALL_32) {
			if (!get_and_print_syscall_32(&regs, child, &status)) break ;
		}
		else {
			if (!get_and_print_syscall_64(&regs, child, &status)) break ;
		}
	}
	dprintf(STDERR_FILENO, "+++ exited with %d +++\n", WEXITSTATUS(status));
}

void		start_tracing(char *bin, char **av_bin, char **env)
{
	pid_t		child;

	if ((child = fork()) == -1)
		die("waitpid", child);
	if (child == 0)
		tracee(bin, av_bin, env);
	else
		tracer(child);
}

int			main(int ac, char **av, char **env)
{
	char		*bin_path;

	if (ac < 2) {
		puts("ft_strace: must have PROG [ARGS]");
		return (EXIT_FAILURE);
	}
	bin_path = get_bin_path(av[1]);
	if (!bin_path)
		exit(EXIT_FAILURE);
	start_tracing(bin_path, ++av, env);
	free(bin_path);
	return (0);
}
