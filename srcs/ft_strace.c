#include "ft_strace.h"

void		start_trace(char *prog, char **env)
{
	int			status;
	pid_t		child;
	uint64_t 	old;

	child = fork();
	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		if ((status = execv(prog, env)) == -1)
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
	int			arg_prog;
	char		*abs_path;

	if (ac < 2)
	{
		puts("ft_strace: must have PROG [ARGS]");
		return (EXIT_FAILURE);
	}
	arg_prog = 0;
	while (++arg_prog < ac)
	{
		abs_path = get_absolute_path(av[arg_prog]);
		if (!abs_path)
			continue ;
		start_trace(abs_path, env);
		free(abs_path);
	}
	return (0);
}
