/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:07:59 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/17 13:20:32 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


char	*check_pipes_cmd(char *cmd, t_shell *shell)
{
	char	*path;
	char	**split;
	char	*full_path;
	char	*ret_cmd;
	int		i;
	
	i = 0;
	path = getenv("PATH");
	split = ft_split(path, ':');
	while (split[i])
	{
		full_path = ft_strjoin(split[i], "/");
		ret_cmd = ft_strjoin(full_path, cmd);
		if (!(access(ret_cmd, X_OK)))
			return (ret_cmd);
		else
		{
			free(ret_cmd);
			free(full_path);
		}
		i++;
	}
	return (NULL);
}

int	parse_pipes(t_shell *shell)
{
	int		i;
	char	*cmd;

	i = 0;
	while (i <= shell->n_pipes && shell->cmds_pipe[i])
	{
		cmd = check_pipes_cmd(shell->cmds_pipe[i][0], shell);
		if (!cmd)
		{
			printf("Minishell: %s: command not found\n", shell->cmds_pipe[i][0]);
			return (0);
		}
		free(shell->cmds_pipe[i][0]);
		shell->cmds_pipe[i][0] = ft_strdup(cmd);
		free(cmd);
		i++;
	}
	return (0);
}