/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:56:24 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/16 21:21:11 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*add_slash(char *path)
{
	char	*ret_path;

	if (!path)
		return (NULL);
	ret_path = ft_strjoin(path, "/");
	return (ret_path);
}

char	*search_cmd(char *cmd, char	**paths)
{
	char	*aux;
	char	*full_path;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (paths[i])
	{
		aux = add_slash(paths[i]);
		full_path = ft_strjoin(aux, cmd);
		free(aux);
		//printf("ret_cmd: %s\n", ret_cmd);
		if (!(access(full_path, X_OK)))
			return (full_path);
		else
		{
			free(full_path);
		}
		i++;
	}
	//printf("bash: %s: command not found", cmd);
	return (NULL);
}

char	*check_cmd_pipe(char *cmd)
{
	char	*path;
	char	**paths;
	char	*ret_cmd;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	if (!cmd || !path)
		return (NULL);
	if (!(access(cmd, X_OK)))
		ret_cmd = cmd;
	else
		ret_cmd = search_cmd(cmd, paths);
	free(paths);
	return (ret_cmd);
}
