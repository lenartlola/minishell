/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:10:07 by lgyger            #+#    #+#             */
/*   Updated: 2022/01/06 12:11:31 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_unset(char **cmd, t_shell *shell)
{
	int		i;
	t_env	*mem;
	t_env	*des;

	i = 1;
	while (cmd[i])
	{
		mem = shell->env;
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
