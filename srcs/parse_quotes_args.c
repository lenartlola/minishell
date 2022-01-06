/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:27:19 by lgyger            #+#    #+#             */
/*   Updated: 2022/01/06 11:59:42 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int	parse_pipes(t_vars *vars, int *i, t_cmd **tmp, int len)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(&vars->str[*i], "|", 1) == 0
		&& get_type(vars->env, *i) != ENVS)
	{
		if (pipe_handler(vars, *i, len, tmp) == -1)
			return (-1);
		*i += 1;
	}
	else if (vars->str[*i] != ' ')
	{
		ret = args_to_word(vars, *tmp, *i);
		if (ret == -1)
			return (-1);
		*i += ret;
	}
	return (0);
}

int	parse_quotes_args(t_vars *vars, int *i, t_cmd *tmp)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(&vars->str[*i], "\'", 1) == 0
		&& get_type(vars->env, *i) != ENVS)
		ret = parse_simple_quote(vars, tmp, *i) + 1;
	else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0
		&& get_type(vars->env, *i) != ENVS)
		ret = parse_double_quote(vars, tmp, *i) + 1;
	else if ((vars->str[*i] == '<' || vars->str[*i] == '>')
		&& get_type(vars->env, *i) != ENVS)
		ret = redirection(vars, tmp, *i);
	*i += ret;
	if (ret == -1 || ret == -254 || ret == -255)
		return (-1);
	return (ret);
}

int	pipe_counter(char *str, char c)
{
	unsigned int	ret;
	size_t			i;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			ret++;
		i++;
	}
	return (ret);
}
