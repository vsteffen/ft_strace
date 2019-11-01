#include "ft_strace.h"

static bool	check_bin_path_exist(char *path)
{
	struct stat		sb;

	if (stat(path, &sb) == 0)
		return (true);
	return (false);
}

static char	*concat_pathn_prog(char *path_env, size_t path_env_length, char *bin_name)
{
	char *bin_path;

	bin_path = malloc(strlen(path_env) + strlen(bin_name) + 2);
	if (!bin_path)
	{
		printf("ft_strace: malloc: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	strncpy(bin_path, path_env, path_env_length);
	bin_path[path_env_length] = '\0';
	strcat(bin_path, "/");
	strcat(bin_path, bin_name);
	return (bin_path);
}

char		*get_bin_path(char *bin_name)
{
	char 	*path;
	char 	*tmp_path;
	char	*delim;

	path = getenv("PATH");
	if (bin_name 
		&& (bin_name[0] == '/'
		|| (bin_name[0] == '.' && (bin_name[1] == '/'
		|| (bin_name[1] == '.' && bin_name[2] == '/')))))
	{
		if (check_bin_path_exist(bin_name))
			return (strdup(bin_name));
	}
	else
	{
		while (path)
		{
			delim = strchrnul(path, ':');
			tmp_path = concat_pathn_prog(path, (delim - path), bin_name);
			if (check_bin_path_exist(tmp_path))
				return (tmp_path);
			free(tmp_path);
			if (*delim)
				path = ++delim;
			else
				path = NULL;
		}
	}
	dprintf(STDERR_FILENO, "ft_strace: Can't stat '%s': No such file or directory\n", bin_name);
	return (NULL);
}
