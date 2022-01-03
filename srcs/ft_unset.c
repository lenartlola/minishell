#include "../incs/minishell.h"

int	ft_unset(char **cmd, t_shell *shell)
{
	int	i;
	t_env *mem;
	t_env *des;

	i = 1;
	while (cmd[i])
	{
		mem = shell->env;
		while (mem->next)
		{
			if (!ft_strcmp(mem->next->name,cmd[i]))
			{
				mem->next = mem->next->next;
				break;
			}
			mem = mem->next;
		}
		i++;
	}
	return (1);
}
