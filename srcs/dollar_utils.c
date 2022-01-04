/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:27:51 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/04 17:30:21 by lgyger           ###   ########.fr       */
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
	char	*tmp;
	char	*swap;

	q_tmp.start = *i - 1;
	q_tmp.end = *i + 1;
	swap = ft_strdup("");
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

char	*remove_space(char *str)
{
	char	**split;
	char	*out;
	int		i;

	split = ft_split(str, ' ');
	if (!split)
		return (NULL);
	out = malloc(sizeof(char));
	if (!out)
	{
		double_free(split);
		return (NULL);
	}
	*out = '\0';
	i = 0;
	while (split[i])
		if (!join_splt(&out, split, &i))
			return (NULL);
	free(str);
	double_free(split);
	return(out);
}

int	get_limits(char *str, int i)
{
	int	len;

	len = ft_strlen(str);
	while (i < len)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break;
		i++;
	}
	return (i);
}

void	dollar_to_env(t_vars *vars, int *i)
{
	char	*tmp;
	char	*swap;
	t_quotes	q_tmp;

	q_tmp.start = *i - 1;
	q_tmp.end = get_limits(vars->str, *i);
	tmp = ft_substr(vars->str, *i, q_tmp.end - q_tmp.start -1);
	if (!tmp)
	{
		free_vars(vars);
		exit(-1);
	}
	swap = get_env_value(vars, tmp);
	//if (!swap)
	//{
	//	swap = ft_calloc(10, 10);
	//}
	//if (!swap)
	//{
	//	free(swap);
	//	return ;
	//}
	//printf("swap : %s\n", swap);
	if (get_type(vars->quotes, *i) == NONE && swap)
		swap = remove_space(swap);
	//printf("tmp : %i\nswap : %i\n", ft_strlen(tmp) - 1, ft_strlen(swap));
	
	update_quotes_data(vars->quotes, (ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
	*i += (int)(ft_strlen(swap) - 2);
	free(tmp);
	tmp = build_new_tkn(vars, q_tmp, swap);
	if (!tmp)
	{
		free(swap);
		free_vars(vars);
		exit (-1);
	}
	free(swap);
	free(vars->str);
	vars->str = tmp;
}

void	parse_dollar(t_vars *vars, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		//printf("vars -> str : %c\n", vars->str[i]);
		if (vars->str[i] == '$' && vars->str[i + 1] && get_type(vars->quotes, i) != SIMPLE)
		{
			i++;
			if (vars->str[i] == '?' || (!ft_isalpha(vars->str[i])))
			{
				if (vars->str[i] == '?')
					last_dollar_ret(vars, &i);
				else if (!ft_isalpha(vars->str[i]))
					ignore_dollar(vars, &i);
				continue ;
			}
			dollar_to_env(vars, &i);
			len = ft_strlen(vars->str);
		}
		i++;
	}
}
