#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void	test(int sig)
{
	signal(sig, SIG_IGN);
//	printf("wololo\n");
	signal(SIGINT,test);
}


int	main(void)
{
	signal(SIGINT,test);
	while (1)
		pause();
	return 0;
}

