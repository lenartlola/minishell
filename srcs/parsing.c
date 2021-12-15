/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 09:57:44 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/15 13:06:02 by 1mthe0wl         ###   ########.fr       */
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
}

char	*check_cmd(char *cmd)
{
	char	*path;
	int		i;
	char	**split;
	char	*full_path;

	i = 0;
	path = getenv("PATH");
	//printf("Paths: %s\n", path);
	split = ft_split(path, ':');
	while (split[i])
	{
		//printf("split: %s\n", split[i]);
		full_path = ft_strjoin(split[i], "/");
		//printf("split: %s\n", ret_cmd);
		if (check_env(full_path, cmd))
		{
			printf("OK\n");
			break ;
		}
		else
		{
			printf("KO\n");
		}
		i++;
	}
}

int	parsing(t_shell *shell)
{
	if (shell->n_pipes)
		printf("Pipes\n");
	else
	{
		check_cmd(shell->tokens[0]);
	}
}
