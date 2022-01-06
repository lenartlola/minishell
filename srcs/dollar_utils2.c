/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:46:49 by lgyger            #+#    #+#             */
/*   Updated: 2022/01/06 12:50:07 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	update_quotes_data(t_quotes *quotes, int size, int i)
{
	t_quotes	*tmp;

	tmp = quotes;
	while (tmp)
	{
		if (tmp->start >= i)
			tmp->start += size;
		if (tmp->end >= i)
			tmp->end += size;
		tmp = tmp->next;
	}
}

void	last_dollar_ret(t_vars *vars, int *i)
{
	char		*tmp;
	char		*swap;
	t_quotes	q_tmp;

	swap = ft_itoa(*vars->last_ret);
	if (!swap)
	{
		free_vars(vars);
		exit(-1);
	}
	q_tmp.start = *i - 1;
	q_tmp.end = *i + 1;
	update_quotes_data(vars->quotes, (ft_strlen(swap) - 2), *i);
	tmp = build_new_tkn(vars, q_tmp, swap);
	if (!tmp)
	{
		free(swap);
		free_vars(vars);
		exit(-1);
	}
	free(vars->str);
	vars->str = tmp;
	*i += ft_strlen(swap) -1;
	free(swap);
}

void	ignore_dollar(t_vars *vars, int *i)
{
	t_quotes	q_tmp;
	char		*tmp;
	char		*swap;

	q_tmp.start = *i - 1;
	q_tmp.end = *i + 1;
	swap = ft_strdup("");
	if (!swap)
	{
		free_vars(vars);
		exit(-1);
	}
	update_quotes_data(vars->quotes, -2, *i);
	*i -= 2;
	tmp = build_new_tkn(vars, q_tmp, swap);
	if (!tmp)
	{
		free(swap);
		free_vars(vars);
		exit(-1);
	}
	free(swap);
	free (vars->str);
	vars->str = tmp;
}

char	*get_env_value(t_vars *vars, char *name)
{
	char	*tmp;
	t_env	*envs;

	envs = vars->env_vars;
	if (check_path_env(&envs, name) == 0)
		return (NULL);
	if (envs->value == NULL)
		return (NULL);
	else
		tmp = ft_strdup(envs->value);
	if (!tmp)
	{
		free(name);
		free_vars(vars);
		exit (-1);
	}
	return (tmp);
}

int	join_splt(char **out, char **split, int *i)
{
	char	*tmp;

	tmp = ft_strjoin(*out, split[*i]);
	if (!tmp)
	{
		free(*out);
		double_free(split);
		return (0);
	}
	free(*out);
	*out = tmp;
	if (split[*i + 1])
	{
		tmp = ft_strjoin(*out, "");
		if (!tmp)
		{
			free(*out);
			double_free(split);
			return (0);
		}
		free(*out);
		*out = tmp;
	}
	*i += 1;
	return (1);
}
