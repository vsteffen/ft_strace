# include <unistd.h>

int main(int ac, char **av, char **env)
{
	execve("./32", av + 1, env);
	write(1, "\n", 1);
	execve("./32", av + 1, env);
	return 0;
}
