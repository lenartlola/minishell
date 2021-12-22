/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:05:09 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/22 12:04:03 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_vars(t_vars *vars, t_shell *shell)
{
	vars->cmd = shell->cmd;
	vars->str = shell->cmdline;
	vars->quotes = init_quotes(-1, -1, NONE);
	if (!vars->quotes)
	{
		free_cmd(vars->cmd);
		free(vars->str);
	}
}

void	c_free_vars(t_vars *vars)
{
	if (vars->cmd)
		free_cmd(vars->cmd);
	if (vars->str)
		free(vars->str);
	if (vars->quotes)
		free_quotes(vars->quotes);
}

void	free_vars(t_vars *vars)
{
	if (vars->cmd)
		free_cmd(vars->cmd);
	if (vars->str)
		free(vars->str);
	if (vars->quotes)
		free_quotes(vars->quotes);
}
