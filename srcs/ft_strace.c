#include "ft_strace.h"

bool		is_executable(char *path)
{
	struct stat		sb;

	if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (true);
	return (false);
}

char		*concat_path_prog(char *path_env, char *prog_name)
{
	char *abs_path;

	abs_path = malloc(strlen(path_env) + strlen(prog_name) + 2);
	if (!abs_path)
	{
		puts("Failed to allocate memory with malloc\n");
		exit(EXIT_FAILURE);
	}
	strcpy(abs_path, path_env);
	strcat(abs_path, "/");
	strcat(abs_path, prog_name);
	return (abs_path);
}

char		*get_absolute_path(char *prog_name)
{
	char *path;
	char *path_dirs;
	char *tmp_path;

	path = getenv("PATH");
	tmp_path = concat_path_prog(".", prog_name);
	if (is_executable(tmp_path))
		return (tmp_path);
	for (path_dirs = strtok(path, ",:"); path_dirs; path_dirs = strtok(NULL, ":"))
	{
		tmp_path = concat_path_prog(path_dirs, prog_name);
		if (is_executable(tmp_path))
			return (tmp_path);
		free(tmp_path);
	}

	return (NULL);
}

void		start_trace(char *prog, char **env)
{
	pid_t		child;
	uint64_t 	old;

	child = fork();
	if (child == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execv(prog, env);
		exit(1);
	}
	else {
		int status;
		struct user_regs_struct regs;

		old = 0;
		wait(&status);
		while (1) {
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (old != regs.rip) {
				printf("rip: 0x%llx\n", regs.rip);
				old = regs.rip;
			}
			ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
			waitpid(child, &status, 0);
			if (WIFEXITED(status))
				break ;
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
		{
			printf("ft_strace: %s: Executable not found\n", av[arg_prog]);
			continue ;
		}
		(void)env;
		// start_trace(av[arg_prog], env);
		// sleep(3);
		free(abs_path);
	}
	return (0);
}
