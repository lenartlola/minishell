/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:33:06 by hsabir            #+#    #+#             */
/*   Updated: 2022/03/13 15:14:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	double_free(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

void	free_all(t_shell *shell, int exit_p, char *str)
{
	if (shell->std_in > 0)
		close_error(shell->std_in);
	if (shell->std_out > 1)
		close_error(shell->std_out);
	//free_cmd(shell->cmd);
	rl_clear_history();
	if (exit_p)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
}

void	free_struct()
{
	free(g_shell.cmdline);
	free(g_shell.prompt);
	g_shell.cmdline = NULL;
	g_shell.prompt = NULL;
}
