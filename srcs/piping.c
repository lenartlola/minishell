/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:07:59 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2022/01/06 11:57:23 by lgyger           ###   ########.fr       */
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
	t_cmd	*tmp;

	tmp = shell->cmd;
	i = 0;
	while (tmp)
	{
		cmd = check_pipes_cmd(tmp->token[0], shell);
		if (!cmd)
		{
			shell->pipe_cmd_exist = 0;
			printf("minishell: %s: command not found\n", shell->cmd->token[i]);
			return (0);
		}
		shell->pipe_cmd_exist = 1;
		free(tmp->token[0]);
		shell->cmd->token[i] = ft_strdup(cmd);
		free(cmd);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

int	check_after_pipe(t_vars *vars, int i, int len, t_cmd *tmp)
{
	if (!tmp->token[0] && !tmp->redirection[0])
	{
		printf("minnishell: syntax error near unexpected token `|'\n");
		*vars->last_ret = 258;
		return (-1);
	}
	i += trim_spaces(&vars->str[i]);
	while (i < len)
	{
		if (vars->str[i] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			*vars->last_ret = 258;
			return (-1);
		}
		else
			return (1);
		i++;
	}
	printf("minishell: unxpected error\n");
	*vars->last_ret = 258;
	return (-1);
}

int	pipe_handler(t_vars *vars, int i, int len, t_cmd **tmp)
{
	if (check_after_pipe(vars, (i + 1), len, *tmp) == -1)
		return (-1);
	(*tmp)->next = init_cmd();
	if (!(*tmp)->next)
		free_vars(vars);
	*tmp = (*tmp)->next;
	return (0);
}
