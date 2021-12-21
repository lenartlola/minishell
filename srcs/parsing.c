/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 09:57:44 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/21 14:37:41 by lgyger           ###   ########.fr       */
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
		{
			free(ret_join);
			return (1);
		}
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
	char	*full_cmd;
	i = 0;
	path = getenv("PATH");
	split = ft_split(path, ':');
	while (split[i])
	{
		full_path = ft_strjoin(split[i], "/");
		if (check_env(full_path, cmd))
		{
			full_cmd = ft_strjoin(full_path, cmd);
			exec_path_cmd(full_cmd, shell);
			free(split);
			free(full_path);
			free(full_cmd);
			break ;
		}
		free(split[i]);
		free(full_path);
		i++;
	}
	return (NULL);
}
int	builtin(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->tokens[i])
	{
		if (!ft_strncmp(shell->tokens[i],"env",3))
			return(ft_env(shell));
		else if (!ft_strncmp(shell->tokens[i],"echo",4))
			return (ft_echo(shell->tokens + i));
		else if (!ft_strncmp(shell->tokens[i],"cd",2))
			return (ft_cd(shell->tokens + 1, shell));
		else if (!ft_strncmp(shell->tokens[i],"export",6))
			return (ft_export(shell->tokens,shell));
		else if (!ft_strncmp(shell->tokens[i],"unset",5))
			return(ft_unset(shell->tokens,shell));
		i++;
	}
	return (0);
}
void	get_cmd(t_shell *shell)
{
	unsigned int i;
	unsigned int a;

	a = 0;
	i = 0;

	if (!builtin(shell))
		check_cmd(shell->tokens[0], shell);
}
int	parsing(t_shell *shell)
{
	if (shell->n_pipes)
	{
		if (shell->pipe_flag == 1)
		{
			parse_pipes(shell);
		}
	}
	else
	{
		get_cmd(shell);
	}
	return (1);
}
