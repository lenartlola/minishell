/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:07:59 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2022/01/20 12:00:11 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//int	check_after_pipe(t_vars *vars, int i, int len, t_cmd *tmp)
//{
//	if (!tmp->token[0] && !tmp->redirection[0])
//	{
//		printf("minnishell: syntax error near unexpected token `|'\n");
//		*vars->last_ret = 258;
//		return (-1);
//	}
//	i += trim_spaces(&vars->str[i]);
//	while (i < len)
//	{
//		if (vars->str[i] == '|')
//		{
//			printf("minishell: syntax error near unexpected token `|'\n");
//			*vars->last_ret = 258;
//			return (-1);
//		}
//		else
//			return (1);
//		i++;
//	}
//	printf("minishell: unxpected error\n");
//	*vars->last_ret = 258;
//	return (-1);
//}
//
//int	pipe_handler(t_vars *vars, int i, int len, t_cmd **tmp)
//{
//	if (check_after_pipe(vars, (i + 1), len, *tmp) == -1)
//		return (-1);
//	(*tmp)->next = init_cmd();
//	if (!(*tmp)->next)
//		free_vars(vars);
//	*tmp = (*tmp)->next;
//	return (0);
//}
