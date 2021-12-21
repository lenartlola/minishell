/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_enviro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:24:25 by lgyger            #+#    #+#             */
/*   Updated: 2021/12/21 16:24:27 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_list	*enviroinit(char **ev)
{
	int		i;
	t_list	*lst;
	t_list	*tmp;

	i = 0;
	lst = ft_lstnew(ev[i]);
	while (ev[i])
	{
		tmp = ft_lstnew(ev[i]);
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	tmp = ft_lstnew("OLDPWD");
	ft_lstadd_back(&lst, tmp);
	return (lst);
}
