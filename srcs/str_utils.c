/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:49:31 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/22 16:45:33 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	get_c_index(char *str, char c)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	trim_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	is_sep(char c)
{
	if (c == 60 || c == 62 || c == 32 || c == 124)
		return (1);
	return (0);
}

int	quote_counter(t_vars *vars, int start, int end)
{
	t_quotes	*tmp;
	int			count;

	count = 0;
	while (start <= end)
	{
		tmp = vars->quotes;
		while (tmp)
		{
			if (start == tmp->start || start == tmp->end)
				count++;
			tmp = tmp->next;
		}
		start++;
	}
	return (count);
}

int	quote_is_data(t_vars *vars, int i)
{
	t_quotes	*tmp;

	tmp = vars->quotes;
	while (tmp)
	{
		if (i == tmp->start || i == tmp->end)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*substr_quote(t_vars *vars, int start, int end)
{
	int		cut;
	char	*tmp;
	int		i;

	cut = quote_counter(vars, start, end);
	tmp = malloc(sizeof(char) * (end - start - cut + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		if (quote_is_data(vars, start) == 1)
			start++;
		else
		{
			tmp[i] = vars->str[i];
			i++;
			start++;
		}
	}
	tmp[i] = '\0';
	return (tmp);
}
