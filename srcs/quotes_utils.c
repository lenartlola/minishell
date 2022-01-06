/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:13:11 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/06 11:52:42 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_quotes	*init_quotes(int start, int end, t_type type)
{
	t_quotes	*quotes;

	quotes = malloc(sizeof(t_quotes));
	if (!quotes)
		return (NULL);
	quotes->next = NULL;
	quotes->start = start;
	quotes->end = end;
	quotes->type = type;
	return (quotes);
}

void	free_quotes(t_quotes *quotes)
{
	t_quotes	*tmp;

	while (quotes)
	{
		tmp = quotes->next;
		free(quotes);
		quotes = NULL;
		quotes = tmp;
	}
}

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

int	quotes_error(void)
{
	printf("minishell: syntax error unclosed quote\n");
	return (-1);
}

void	quote_error_exit(t_vars *vars)
{
	free_vars(vars);
	perror("Error\n");
	exit(EXIT_FAILURE);
}
