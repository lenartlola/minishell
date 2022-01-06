/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:24:35 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/06 12:00:35 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	add_slash(char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
		{
			double_free(path);
			return (-1);
		}
		free(path[i]);
		path[i] = tmp;
		i++;
	}
	return (1);
}

int	check_path_and_permission(char *path, t_cmd *cmd,
	t_shell *shell, char **per)
{
	struct stat	stat_path;

	if (stat(path, &stat_path) == -1)
	{
		shell->ret = 127;
		return (0);
	}
	if (cmd->path != NULL)
		free(cmd->path);
	cmd->path = ft_strdup(path);
	if (access(path, X_OK) != 0)
	{
		if (*per == NULL)
			*per = ft_strdup(cmd->path);
		shell->ret = 126;
		return (0);
	}
	shell->ret = 0;
	return (1);
}

void	search_path(char **tmp_path, t_shell *shell)
{
	char	*path;
	char	*per;
	int		i;

	i = -1;
	path = NULL;
	per = NULL;
	while (tmp_path[++i])
	{
		path = ft_strjoin(tmp_path[i], *shell->cmd->token);
		if (path == NULL)
			return ;
		if (check_path_and_permission(path, shell->cmd, shell, &per))
		{
			free(path);
			break ;
		}
		free(path);
	}
	if (shell->cmd->path != NULL && shell->ret == 126)
	{
		free(shell->cmd->path);
		shell->cmd->path = per;
	}
	double_free (tmp_path);
}

void	check_error(char *path, char *prog, t_shell *shell)
{
	if (path == NULL)
		printf("minish: %s: command not found\n", prog);
	else if (shell->ret > 0)
		perror(path);
}

int	get_path_exec(t_shell *shell)
{
	t_env	*env;
	char	**tmp_path;

	env = shell->env;
	if (absolute_path(shell))
		return (shell->ret);
	tmp_path = split_tab(shell->env);
	if (tmp_path == NULL || (check_path_env(&env, "PATH")
			&& !env->value) || !*env->value)
	{
		shell->cmd->path = ft_strdup(*shell->cmd->token);
		return (is_xok(*shell->cmd->token));
	}
	else
		search_path(tmp_path, shell);
	check_error(shell->cmd->path, *shell->cmd->token, shell);
	return (shell->ret);
}
