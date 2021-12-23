/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:07:59 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/23 14:52:53 by hsabir           ###   ########.fr       */
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
		{
			free(full_path);
			free(split[i]);
			free(split);
			return (ret_cmd);
		}
		else
		{
			free(ret_cmd);
			free(full_path);
			free(split[i]);
		}
		i++;
	}
	return (NULL);
}

int	get_pipes(t_shell *shell)
{
	int		i;
	char	*cmd;

	i = 0;
	//while (i <= shell->n_pipes && shell->cmds_pipe[i])
	while (shell->cmd->next)
	{
		cmd = check_pipes_cmd(shell->cmd->token[i], shell);
		printf("Dpipe %s \n", shell->cmd->token[i]);
		if (!cmd)
		{
			shell->pipe_cmd_exist = 0;
			printf("minishell: %s: command not found\n", shell->cmd->token[i]);
			return (0);
		}
		shell->pipe_cmd_exist = 1;
		free(shell->cmd->token[i]);
		shell->cmd->token[i] = ft_strdup(cmd);
		free(cmd);
		shell->cmd = shell->cmd->next;
	}
	return (0);
}

int	check_after_pipe(t_vars *vars, int i, int len, t_cmd *tmp)
{
	if (!tmp->token[0])
	{
		printf("minnishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	i += trim_spaces(&vars->str[i]);
	while (i < len)
	{
		if (vars->str[i] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (-1);
		}
		else
			return (1);
		i++;
	}
	printf("minishell: unxpected error\n");
	return (-1);
}

int	pipe_handler(t_vars *vars, int i, int len, t_cmd **tmp)
{
	if (check_after_pipe(vars, (i + 1), len, *tmp) == -1)
		return (-1);
	printf("vsrs token : %s\n", vars->cmd->token[1]);
	(*tmp)->next = init_cmd();
	if (!(*tmp)->next)
		free_vars(vars);
	*tmp = (*tmp)->next;
	return (0);
}
