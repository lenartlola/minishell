/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:24:35 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/31 16:55:39 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	is_xok(char *path)
{
	struct stat	stat_path;
	int	ret;

	ret = 0;
	if (stat(path, &stat_path) == -1)
	{
		perror(path);
		return (127);
	}
	if (S_ISDIR(stat_path.st_mode))
	{
		printf("minish: %s: is a directory\n", path);
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		perror(path);
		ret = 126
	}
	return (ret);
}

int	absolute_path(t_shell *shell)
{
	if (ft_strchr(*shell->cmd->token, '/') || **shell->cmd->token == '.')
	{
		shell->cmd->path = ft_strdup(*shell->cnd->token);
		shell->ret = is_xok(shell->cmd->path);
		return (1);
	}
	return (0);
}

int	get_path(t_shell *shell, char **env)
{
	char	**tmp_path;

	if (absolute_path(shell))
		return (shell->ret);
}
