/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:10:07 by lgyger            #+#    #+#             */
/*   Updated: 2022/03/13 15:03:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_unset(char **cmd)
{
	int		i;
	t_env	*mem;
	t_env	*des;

	i = 1;
	while (cmd[i])
	{
		mem = g_shell.env;
		while (mem->next)
		{
			if (!ft_strcmp(mem->next->name, cmd[i]))
			{
				mem->next = mem->next->next;
				break ;
			}
			mem = mem->next;
		}
		i++;
	}
	return (1);
}
