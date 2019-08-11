#include "ft_strace.h"

void		tracee(char *bin, char **av_bin, char **env)
{
	int		status;

	kill(getpid(), SIGSTOP);
	if ((status = execve(bin, av_bin, env)) == -1)
	{
		printf("ft_strace: exec: %s\n", strerror(errno));
		exit(status);
	}
	exit(0);
}

// void		ptrace_event_handler(int status)
// {
// 	status = status >> 8;
// 	if (status == PTRACE_EVENT_VFORK)
// 		printf("-> PTRACE_EVENT_VFORK");
// 	else if (status == PTRACE_EVENT_FORK)
// 		printf("-> PTRACE_EVENT_FORK");
// 	else if (status == PTRACE_EVENT_CLONE)
// 		printf("-> PTRACE_EVENT_CLONE");
// 	else if (status == PTRACE_EVENT_VFORK_DONE)
// 		printf("-> PTRACE_EVENT_VFORK_DONE");
// 	else if (status == PTRACE_EVENT_EXEC)
// 		printf("-> PTRACE_EVENT_EXEC");
// 	else if (status == PTRACE_EVENT_EXIT)
// 		printf("-> PTRACE_EVENT_EXIT");
// 	else if (status == PTRACE_EVENT_STOP)
// 		printf("-> PTRACE_EVENT_STOP");
// 	else if (status == PTRACE_EVENT_SECCOMP)
// 		printf("-> PTRACE_EVENT_SECCOMP");
// }

char		*identify_si_code(struct s_strace *strace, siginfo_t *sig)
{
	if (sig->si_code == SI_KERNEL)
		return ("SI_KERNEL");
	if (sig->si_code <= 0)
	{
		struct s_si_code_reg  *ptr = strace->si_code_reg;
		for (uint8_t i = 0; i < SI_CODE_REG_NB; i++, ptr++)
		{
			if (sig->si_code == strace->si_code_reg[i].si_code)
				return (strace->si_code_reg[i].to_str);
		}
		return ("UNKNOWN");
	}
	struct s_si_code  *ptr = strace->si_code;
	for (uint8_t i = 0; i < SI_CODE_NB; i++, ptr++)
	{
		if (sig->si_signo == strace->si_code[i].si_signo)
		{
			for (uint8_t j = i; j < SI_CODE_NB; j++, ptr++)
			{
				if (sig->si_code == strace->si_code[j].si_code)
					return (strace->si_code[j].to_str);
				if (sig->si_signo != strace->si_code[j].si_signo)
					return ("UNKNOWN");
			}

		}
	}
	return ("UNKNOWN");
}

void		print_sig(struct s_strace *strace, pid_t child)
{
	siginfo_t		sig;

	if (ptrace(PTRACE_GETSIGINFO, child, NULL, &sig) == -1)
	{
		printf("ft_strace: ptrace: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("--- %s {si_signo=%s, si_code=%s, \n", strace->signo_to_str[sig.si_signo], strace->signo_to_str[sig.si_signo], identify_si_code(strace, &sig));
}

bool		handle_syscall(struct s_strace *strace, pid_t child, int *status)
{
	while (42) {
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, status, __WALL);
		if (WIFSTOPPED(*status))
		{
			if (WSTOPSIG(*status) & 0x80)
				return (true);
			else
				print_sig(strace, child);
		}
		if (WIFEXITED(*status))
			return (false);
	}
}

void		tracer(struct s_strace *strace, pid_t child)
{
	int		status;

	if (ptrace(PTRACE_SEIZE, child, NULL, NULL) == -1)
	{
		printf("ft_strace: ptrace: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (waitpid(child, &status, __WALL) == -1)
	{
		printf("ft_strace: waitpid: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD))
	{
		printf("ft_strace: ptrace: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(42)
	{
		if (!handle_syscall(strace, child, &status))
			break;
		fprintf(stderr, "SYSCALL ");
		if (!handle_syscall(strace, child, &status))
		{
			fprintf(stderr, "WITHOUT RETURN\n");
			break;
		}
		fprintf(stderr, "AND RETURN\n");
	}
	printf("+++ exited with %d +++\n", WEXITSTATUS(status));
}

void		start_tracing(struct s_strace *strace, char *bin, char **av_bin, char **env)
{
	pid_t		child;

	if ((child = fork()) == -1)
	{
		printf("ft_strace: waitpid: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (child == 0)
		tracee(bin, av_bin, env);
	else
		tracer(strace, child);
}

int			main(int ac, char **av, char **env)
{
	char		*bin_path;

	if (ac < 2)
	{
		puts("ft_strace: must have PROG [ARGS]");
		return (EXIT_FAILURE);
	}
	bin_path = get_bin_path(av[1]);
	if (!bin_path)
		exit(EXIT_FAILURE);

	struct s_strace strace = {SI_SIGNO, SI_CODE, SI_CODE_REG};
	start_tracing(&strace, bin_path, ++av, env);
	free(bin_path);
	return (0);
}
