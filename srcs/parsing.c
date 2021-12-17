/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 09:57:44 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/17 12:27:36 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_env(char *path, char *cmd)
{
	int	i;
	char	*ret_join;

	i = 0;
	ret_join = ft_strjoin(path, cmd);
	while (path[i])
	{
		if (!(access(ret_join, X_OK)))
			return (1);
		else
			i++;
	}
	free(ret_join);
	return (0);
}

char	*check_cmd(char *cmd, t_shell *shell)
{
	char	*path;
	int		i;
	char	**split;
	char	*full_path;
	i = 0;
	path = getenv("PATH");
	split = ft_split(path, ':');
	while (split[i])
	{
		full_path = ft_strjoin(split[i], "/");
		if (check_env(full_path, cmd))
		{
				exec_path_cmd(ft_strjoin(full_path, cmd), shell);
			break ;
		}
		else
		{
//			printf("KO\n");
		}
		i++;
	}
	return (NULL);
}
void	get_cmd(t_shell *shell)
{
	unsigned int i;
	unsigned int a;

	a = 0;
	i = 0;
	while (shell->cmdline[i])
	{
		if (shell->cmdline[i] == '&' || shell->cmdline[i] == '|')
		{
			shell->cmds = ft_substr(shell->cmdline,a,i);
			a = i + 2;
			shell->tokens = ft_split(shell->cmds, ' ');
			check_cmd(shell->tokens[0], shell);
			i += 2;
		}
		else
			i++;
	}
	shell->cmds = ft_substr(shell->cmdline,a,i);
	check_cmd(shell->tokens[0], shell);
}
int	parsing(t_shell *shell)
{
	unsigned int 	i;
	char			*cmd;

	i = 0;
	if (shell->n_pipes)
	{
		if (!(parse_pipes(shell)))
			return (1);
	}
	else
	{
		get_cmd(shell);
	}
	return (1);
}
