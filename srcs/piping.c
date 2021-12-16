/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:07:59 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/16 16:18:41 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*int	check_env(char *path, char *cmd)
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
}*/

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
		//printf("ret_cmd: %s\n", ret_cmd);
		if (!(access(ret_cmd, X_OK)))
			return (ret_cmd);
		else
		{
			free(ret_cmd);
			free(full_path);
		}
		i++;
	}
	//printf("bash: %s: command not found", cmd);
	return (NULL);
}

int	parse_pipes(t_shell *shell)
{
	int		i;
	char	*cmd;

	i = 0;
	while (i < shell->n_pipes)
	{
		//printf("cmd_pipe: %s\n", shell->cmds_pipe[i][0]);
		cmd = check_pipes_cmd(shell->cmds_pipe[i][0], shell);
		if (!cmd)
		{
			printf("Minishell: %s: command not found\n", shell->cmds_pipe[i][0]);
			return (0);
		}
		free(shell->cmds_pipe[i][0]);
		//shell->cmds_pipe[i][0] = ft_substr(cmd);
		shell->cmds_pipe[i][0] = ft_strdup(cmd);
		//printf("cmds_pipe: %s\n", shell->cmds_pipe[i][0]);
		free(cmd);
		i++;
	}
	//printf("ret_cmd");
	return (0);
	//check_pipes_cmd(shell->tokens[i][0]);
	//printf("piping\n");
}
