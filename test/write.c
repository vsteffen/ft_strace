# include <unistd.h>

int main()
{
	write(1, "42\n", 3);
	return 0;
}
