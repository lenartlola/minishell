#include <unistd.h>
#include <stdio.h>
#  include <readline/readline.h>

int	main(int ac, char *av[])
{
	char *c;
	c = readline(">>");
	printf("\n");
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();

	return 1;
}
