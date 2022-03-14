/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:27:51 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/07 13:19:29 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//char	*remove_space(char *str)
//{
//	char	**split;
//	char	*out;
//	int		i;
//
//	split = ft_split(str, ' ');
//	if (!split)
//		return (NULL);
//	out = malloc(sizeof(char));
//	if (!out)
//	{
//		double_free(split);
//		return (NULL);
//	}
//	*out = '\0';
//	i = 0;
//	while (split[i])
//		if (!join_splt(&out, split, &i))
//			return (NULL);
//	free(str);
//	double_free(split);
//	return (out);
//}
//
//int	get_limits(char *str, int i)
//{
//	int	len;
//
//	len = ft_strlen(str);
//	while (i < len)
//	{
//		if (!ft_isalnum(str[i]) && str[i] != '_')
//			break ;
//		i++;
//	}
//	return (i);
//}
//
//void	dollar_to_env(t_vars *vars, int *i)
//{
//	char		*tmp;
//	char		*swap;
//	t_quotes	q_tmp;
//
//	q_tmp.start = *i - 1;
//	q_tmp.end = get_limits(vars->str, *i);
//	tmp = ft_substr(vars->str, *i, q_tmp.end - q_tmp.start - 1);
//	if (!tmp)
//	{
//		free_vars(vars);
//		exit(-1);
//	}
//	swap = get_env_value(vars, tmp);
//	if (get_type(vars->quotes, *i) == NONE && swap)
//		swap = remove_space(swap);
//	update_quotes_data(vars->quotes,
//		(ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
//	*i += (int)(ft_strlen(swap) - 2);
//	free(tmp);
//	tmp = build_new_tkn(vars, q_tmp, swap);
//	if (!tmp)
//	{
//		free(swap);
//		free_vars(vars);
//		exit (-1);
//	}
//	free(swap);
//	free(vars->str);
//	vars->str = tmp;
//}
//
//int	ft_space(char c)
//{
//	if (c == 32 || (c >= 9 && c <= 13))
//		return (1);
//	return (0);
//}
//
///*
// * Looking for a $ sign and check if it's not in a single quotes,
// * if it is so just continue, otherwise check if after it is a ?,
// * and if it is call a function to find the last return value.
// */
//
//void	parse_dollar(t_vars *vars, int len)
//{
//	int	i;
//
//	i = 0;
//	while (i < len && vars->str[i])
//	{
//		if (vars->str[i] == '$' && vars->str[i + 1] && get_type(vars->quotes,
//				i) != SIMPLE)
//		{
//			i++;
//			if (vars->str[i] == '?' || (!ft_isalpha
//					(vars->str[i]) && vars->str[i] != '_'))
//			{
//				if (vars->str[i] == '?')
//					last_dollar_ret(vars, &i);
//				else if (!ft_isalpha(vars->str[i]) && (!ft_space(vars->str[i]))
//						&& vars->str[i] != '\"')
//					ignore_dollar(vars, &i);
//				continue ;
//			}
//			dollar_to_env(vars, &i);
//			len = ft_strlen(vars->str);
//		}
//		i++;
//	}
//}
