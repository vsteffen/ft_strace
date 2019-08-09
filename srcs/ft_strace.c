#include "ft_strace.h"

void		start_trace(char *prog, char **av, char **env)
{
	int			status;
	pid_t		child;
	uint64_t 	old;

	child = fork();
	if (child == 0) {
		// printf("ptrace -> %ld\n", ptrace(PTRACE_SEIZE, getppid(), NULL, NULL));
		if (ptrace(PTRACE_SEIZE, getppid(), NULL, NULL) == -1)
		{
			printf("ft_strace: ptrace: %s\n", strerror(errno));
			exit(1);
		}
		if ((status = execve(prog, av, env)) == -1)
		{
			printf("ft_strace: exec: %s\n", strerror(errno));
			exit(1);
		}
		exit(0);
	}
	else {
		struct user_regs_struct regs;

		old = 0;
		if (wait(&status) == -1)
		{
			printf("ft_strace: wait: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		while (1) {
			if (WIFEXITED(status))
			{
				printf("+++ exited with %d +++\n", WEXITSTATUS(status));
				return ;
			}
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (old != regs.rip) {
				// printf("rip: 0x%llx\n", regs.rip);
				old = regs.rip;
			}
			ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
			if (waitpid(child, &status, 0) == -1)
			{
				printf("ft_strace: waitpid: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
	}
}

int			main(int ac, char **av, char **env)
{
	char		*abs_path;

	if (ac < 2)
	{
		puts("ft_strace: must have PROG [ARGS]");
		return (EXIT_FAILURE);
	}
	abs_path = get_absolute_path(av[1]);
	if (!abs_path)
		exit(EXIT_FAILURE);
	start_trace(abs_path, av + 1, env);
	free(abs_path);
	return (0);
}
