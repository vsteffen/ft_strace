#include "ft_strace.h"

void		die(char *fn_fail, pid_t child) {
	dprintf(STDERR_FILENO, "ft_strace: ");
	perror(fn_fail);
	kill(child, SIGKILL);
	exit(EXIT_FAILURE);
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

void		get_registers_values(union x86_64_regs *regs, int child) {
	if (ptrace(PTRACE_GETREGS, child, NULL, regs) == -1)
		die("ptrace", child);
}

void		initialize_tracer(pid_t child) {
	if (ptrace(PTRACE_SEIZE, child, NULL, NULL) == -1)
		die("ptrace", child);
	wait_and_block_signals(child, NULL);
	if (ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD))
		die("ptrace", child);
}

void		tracer(pid_t child)
{
	enum e_syscall_arch syscall_arch;
	union x86_64_regs regs;
	struct iovec io = {
		.iov_base = &regs,
		.iov_len = sizeof(regs)
	};

	initialize_tracer(child);
	while(42)
	{
		if (!handle_sig_and_wait_syscall(child, SI_ALIVE))
			break;
		get_registers_values(&regs, child);
		syscall_arch = get_syscall_arch(child, &io);
		if (syscall_arch == SYSCALL_32) {
			if (!get_and_print_syscall_32(&regs, child)) break ;
		}
		else {
			if (!get_and_print_syscall_64(&regs, child)) break ;
		}
	}
	handle_sig_and_wait_syscall(child, SI_DEAD);
}

void		tracee(char *bin, char **av_bin, char **env)
{
	int		status;

	kill(getpid(), SIGSTOP);
	if ((status = execve(bin, av_bin, env)) == -1)
		exit(1);
	exit(0);
}

void		start_tracing(char *bin, char **av_bin, char **env)
{
	pid_t		child;

	if ((child = fork()) == -1)
		die("fork", child);
	if (child == 0)
		tracee(bin, av_bin, env);
	else
		tracer(child);
}

int			main(int ac, char **av, char **env)
{
	char		*bin_path;

	if (ac < 2) {
		dprintf(STDERR_FILENO, "ft_strace: must have PROG [ARGS]\n");
		return (EXIT_FAILURE);
	}
	bin_path = get_bin_path(av[1]);
	if (!bin_path)
		exit(EXIT_FAILURE);
	start_tracing(bin_path, ++av, env);
	free(bin_path);
	return (0);
}
