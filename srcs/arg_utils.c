/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:26:35 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/22 16:19:32 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	copy_args(char **args, char **tmp, char *new)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		tmp[i] = ft_strdup(args[i]);
		if (!tmp[i])
		{
			double_free(tmp);
			return (0);
		}
		i++;
	}
	tmp[i] = ft_strdup(new);
	if (!tmp[i])
	{
		double_free(tmp);
		return (0);
	}
	return (1);
}

char	**append_args(char **args, char *new)
{
	int		i;
	char	**tmp;

	if (!new)
		return (args);
	if (new[0] == '\0')
	{
		free(new);
		return (args);
	}
	i = 0;
	while (args[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!copy_args(args, tmp, new))
		return (NULL);
	tmp[i + 1] = NULL;
	double_free(args);
	free(new);
	return (tmp);
}

int	args_loop(t_vars *vars, int *i)
{
	int	len;
	int	ret;

	len = ft_strlen(vars->str);
	while (*i < len)
	{
		if (vars->str[*i] == ' ')
			break ;
		if (is_sep(vars->str[*i]))
			break;
		else if (ft_strncmp(&vars->str[*i], "\'", 1) == 0)
		{
			ret = get_c_index((&vars->str[*i] + 1), '\'');
			*i += ret + 1;
		}
		else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0)
		{
			ret = get_c_index((&vars->str[*i] + 1), '\"');
			*i += ret + 1;
		}
		if (ret == -1)
			return (-1);
		*i += 1;
	}
	return (0);
}

int	check_empty(t_vars *vars)
{
	if (!vars->cmd->token[0] && vars->quotes->start != -1)
	{
		printf("minishell: %s: command not found\n", vars->cmd->token[0]);
		return (-1);
	}
	return (0);
}

int	args_to_word(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	j = i + 1;
	if (args_loop(vars, &j) == -1)
		return (quotes_error());
	tmp = substr_quote(vars, i, j - 1);
	if (!tmp)
		free_vars(vars);
	current->token = append_args(current->token, tmp);
	if (!current->token)
		free_vars(vars);
	return (j - i);
}
