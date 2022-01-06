/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:59:41 by lgyger            #+#    #+#             */
/*   Updated: 2022/01/06 11:57:51 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	is_xok(char *path)
{
	struct stat	stat_path;
	int			ret;

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
		ret = 126;
	}
	return (ret);
}

int	absolute_path(t_shell *shell)
{
	if (ft_strchr(*shell->cmd->token, '/') || **shell->cmd->token == '.')
	{
		shell->cmd->path = ft_strdup(*shell->cmd->token);
		shell->ret = is_xok(shell->cmd->path);
		return (1);
	}
	return (0);
}

char	**split_tab(t_env *env)
{
	char	**tab;

	tab = NULL;
	if (check_path_env(&env, "PATH"))
	{
		if (env->value)
		{
			tab = ft_split(env->value, ':');
			if (tab == NULL)
				exit(EXIT_FAILURE);
			add_slash(tab);
		}
	}
	return (tab);
}
