#include "ft_strace.h"

void		tracee(char *bin, char **av_bin, char **env)
{
	int		status;

	kill(getpid(), SIGSTOP);
	if ((status = execve(bin, av_bin, env)) == -1) {
		printf("ft_strace: exec: %s\n", strerror(errno));
		exit(status);
	}
	exit(0);
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

void		print_sig(pid_t child)
{
	siginfo_t		si;

	if (ptrace(PTRACE_GETSIGINFO, child, NULL, &si) == -1) {
		printf("ft_strace: ptrace: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("--- %s {si_signo=%s, si_code=%s, si_pid=%d, si_uid=%u, si_status=%d, si_utime=%ld, si_stime=%ld} ---\n",
		si_signo_to_str(&si), si_signo_to_str(&si), si_code_to_str(&si), si.si_pid, si.si_uid, si.si_status, si.si_utime, si.si_stime);
}

bool		handle_sig_and_wait_syscall(pid_t child, int *status)
{
	while (42) {
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, status, __WALL);
		if (WIFSTOPPED(*status)) {
			if (WSTOPSIG(*status) & 0x80)
				return (true);
			else
				print_sig(child);
		}
		if (WIFEXITED(*status))
			return (false);
	}
}

enum e_syscall_arch	get_syscall_arch(pid_t child, struct iovec *io)
{
	#ifdef __x86_64__
		static bool first_time = true;
	#endif

	if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, io)) {
		printf("ft_strace: ptrace: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

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

void		initialize_tracer(pid_t child) {
	int		status;

	if (ptrace(PTRACE_SEIZE, child, NULL, NULL) == -1) {
		printf("ft_strace: ptrace: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (waitpid(child, &status, __WALL) == -1) {
		printf("ft_strace: waitpid: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD)) {
		printf("ft_strace: ptrace: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void		get_registers_values(union x86_64_regs *regs, int child) {
	if (ptrace(PTRACE_GETREGS, child, NULL, regs)) {
		printf("ft_strace: ptrace: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
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

	initialize_tracer(child);
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
	printf("+++ exited with %d +++\n", WEXITSTATUS(status));
}

void		start_tracing(char *bin, char **av_bin, char **env)
{
	pid_t		child;

	if ((child = fork()) == -1) {
		printf("ft_strace: waitpid: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
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
