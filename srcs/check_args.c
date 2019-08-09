#include "ft_strace.h"

static bool	check_bin_exist(char *path)
{
	struct stat		sb;

	if (stat(path, &sb) == 0)
		return (true);
	return (false);
}

static char	*concat_path_prog(char *path_env, char *prog_name)
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
	if (prog_name 
		&& (prog_name[0] == '/'
		|| (prog_name[0] == '.' && (prog_name[1] == '/'
		|| (prog_name[1] == '.' && prog_name[2] == '/')))))
	{
		if (check_bin_exist(prog_name))
			return (strdup(prog_name));
	}
	else
	{
		for (path_dirs = strtok(path, ",:"); path_dirs; path_dirs = strtok(NULL, ":"))
		{
			tmp_path = concat_path_prog(path_dirs, prog_name);
			if (check_bin_exist(tmp_path))
				return (tmp_path);
			free(tmp_path);
		}
	}
	printf("ft_strace: Can't stat '%s': No such file or directory\n", prog_name);
	return (NULL);
}