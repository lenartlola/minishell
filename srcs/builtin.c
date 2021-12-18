#include "../incs/minishell.h"

void	ft_printecho(char *str);

int	ft_echo(char **cmd)
{
	int	i;
	
	i = 1;
	while(cmd[i])
	{
		if(i == 1 && (!ft_strncmp(cmd[1], "-n",2)))
			i++;
		ft_printecho(cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if ((ft_strncmp(cmd[1],"-n",2)))
		printf("\n");
	return (1);
}
void	ft_printecho(char *str)
{
	int	i;
	int	u;

	u = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (u == 0)
				printf("%c",str[i + 1]);
			u = 1;
		}
		if (str[i] != '\\' && u != 1)
			printf("%c",str[i]);
		i++;
	}
}
int	ft_env(void)
{
	int	i;

	i = 0;
	while(g_env[i])
	{
		printf("%s\n",g_env[i]);
		i++;
	}
	return (1);
}
