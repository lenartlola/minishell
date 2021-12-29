/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:57:56 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/29 13:27:33 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	args_r_handler(t_vars *vars, int *i)
{
	if (is_sep(vars->str[*i]))
	{
		ft_printf("minish: syntax error near unexpected token `%c'\n", vars->str[*i]);
		return (-1);
	}
	else if (vars->str[*i] == '\0')
	{
		printf("minish: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	return (1);
}

int	redirection_loop(t_vars *vars, int *i)
{
	int	len;

	len = ft_strlen(vars->str);
	if (args_r_handler(vars, i) == -1)
		return (-1);
	while (*i < len)
	{
		if (is_sep(vars->str[*i]))
			break ;
		else if (ft_strncmp(&vars->str[*i], "\'", 1) == 0)
			*i += get_c_index((&vars->str[*i] + 1). '\'') + 1;
		else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0)
			*i += get_c_index((&vars->str[*i] + 1), '\"') + 1;
		*i += 1;
	}
	return (0);
}

int	redirection(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	int		k;
	char	*tmp;

	j = i + 1;
	if (vars->str[j] == vars->str[j - 1])
		j++;
	tmp = ft_substr(vars->str, i, j - i);
	if (!tmp)
		free_vars(vars);
	current->red = append_args(current->red, tmp);
	if (!current->red)
		free_vars(vars);
	j += trim_spaces(&vars->str[j]);
	k = j;
	if (redirection_loop(vars, &k) == -1)
		return (-1);
	tmp = substr_quote(vars, j, k - 1);
	if (!tmp)
		free_vars(vars);
	current->red = append_args(current->red, tmp);
	if (!current->red)
		free_vars(vars);
	return (k - j);
}
