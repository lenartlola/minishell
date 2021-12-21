#include "../incs/minishell.h"
void verfirst(char **cmd, t_shell *shell)
{
	char *str;
	t_list *mem;
	int	i;

	i = 1;
	mem = shell->ev;
	str = mem->content;
	while (cmd[i] && !ft_strncmp(str,cmd[i],ft_strlen(cmd[i])))
	{
		shell->ev = shell->ev->next;
		free(mem);
		i++;
		mem = shell->ev;
		str = mem->content;
	}
}
int	ft_unset(char **cmd, t_shell *shell)
{
	t_list *mem;
	t_list *tmp;
	char *str;
	int	i;

	i = 1;
	verfirst(cmd,shell);
	mem = shell->ev;
	while (mem && cmd[i])
	{
		tmp = mem->next;
		if (tmp && tmp->content != NULL)
			str = tmp->content;
		if (!ft_strncmp(str,cmd[i],ft_strlen(cmd[i])))
		{
			mem->next = tmp->next;
			free(tmp);
			i++;
			continue ;
		}
		mem = mem->next;
	}
	return (1);
}
