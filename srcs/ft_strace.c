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

bool		handle_syscall(pid_t child, int *status)
{
	while (42) {
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, status, __WALL);
		if (WIFSTOPPED(*status))
		{
			if (WSTOPSIG(*status) & 0x80)
				return (true);
			else
				printf("SIGNAL DETECTED\n");
		}
		if (WIFEXITED(*status))
			return (false);
	}
}

void		tracer(pid_t child)
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
		if (!handle_syscall(child, &status))
			break;
		fprintf(stderr, "SYSCALL ");
		if (!handle_syscall(child, &status))
		{
			fprintf(stderr, "WITHOUT RETURN\n");
			break;
		}
		fprintf(stderr, "AND RETURN\n");
	}
	printf("+++ exited with %d +++\n", WEXITSTATUS(status));
}

void		start_tracing(char *bin, char **av_bin, char **env)
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
		tracer(child);
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
	start_tracing(bin_path, ++av, env);
	free(bin_path);
	return (0);
}
