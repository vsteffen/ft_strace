# include <unistd.h>

int main(int ac, char **av, char **env)
{
	execve("./32", av + 1, env);
	return 0;
}
