/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:59:11 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/20 13:08:38 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_strhas(char *str, char *set)
{
	int	i;

	while (str && *str)
	{
		i = 0;
		while (set && set[i])
		{
			if (*str == set[i])
				return (1);
			i++;
		}
		str++;
	}
	return (0);
}

/*
t_q_vars	*init_q_vars(char **new_tkn, int i)
{
	t_q_vars	*q_vars;

	q_vars = ft_calloc(1, sizeof(q_vars));
	q_vars->i = i;
	q_vars->j = i;
	q_vars->start = new_tkn;
	
}

int	join_token(char **new_tkn, int	i)
{
	t_q_vars	*q_vars;
	int			check;

	q_vars = init_q_vars(new_tkn, i);
	printf("start_o:  %s\n", new_tkn[0]);
	//free(q_vars);
}

int	check_quotes(char **tokens)
{
	int	i;
	char	**new_tkn;

	if (*tokens == NULL)
		return (EXIT_FAILURE);
	i = 0;
	new_tkn = ft_split(*tokens, ' ');
//	printf("new_tkn %s\n",new_tkn[i]);
//	if (*new_tkn == NULL)
//		return (EXIT_FAILURE);
	while(new_tkn[i])
	{
		if (new_tkn[i]  && (ft_strhas((new_tkn)[i], "\'\"") == 1))
		{
			join_token(&new_tkn[i], i);
			//free(new_tkn[i]);
		}
		i++;
	}
	return (0);
}*/
