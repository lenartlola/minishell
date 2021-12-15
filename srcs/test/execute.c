#include <unistd.h>
#include <stdio.h>

int	main(int ac, char *av[])
{
	if (execve(av[1],&av[2],NULL) == 0)
		return 0;
	return 1;
}
