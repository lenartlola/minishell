/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 22:55:45 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2022/03/14 11:55:53 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <minishell.h>
#include "../../incs/minishell.h"

//char	*ft_trim(char *str)
//{
//	char	*ret;
//
//	ret = ft_strtrim(str, " ");
//	free(str);
//	return (ret);
//}
//
///*
// * Check if a pipe exist before or after the quotes,
// * skip the spaces if found,
// */
//
//int	parse_loop(t_vars *vars, int len)
//{
//	t_cmd	*tmp;
//	int		i;
//	int		ret;
//
//	tmp = vars->cmd;
//	i = 0;
//	while (i < len)
//	{
//		i += trim_spaces(&vars->str[i]);
//		ret = parse_quotes_args(vars, &i, tmp);
//		if (ret == -1)
//			return (-1);
//		else if (ret != 0)
//			continue ;
//		if (parse_pipes(vars, &i, &tmp, len) == -1)
//			return (-1);
//	}
//	return (0);
//}

// Re:Bonus

static int	process_char(t_lexadd *la, const char *line, const size_t sz)
{
	if (la->st == ST_GENERAL)
	{
		if (handle_general_state(la, line, sz))
			return (1);
	}
	else
		handle_other_st(la);
	if (la->type == CHAR_NULL)
	{
		if (la->j > 0)
		{
			la->tkn->data[la->j] = '\0';
			la->j = 0;
		}
	}
	return (0);
}

int	tokenizing(const char *line, size_t len, t_lexer *lex)
{
	t_lexadd 	la;
	int 		ret;

	lex->n_tokens = 0;
	if (g_shell.is_expd == FALSE)
		g_shell.tokdel = FALSE;
	if (len == 0 || init_la(&la, lex, len) == 1)
		return (0);
	while (1)
	{
		if (la.i > (int)len)
			break ;
		la.c = line[la.i];
		la.type = get_ctype(la.c);
		if (process_char(&la, line, len))
			return (0);
		la.i++;
		if (la.c == '\0')
			break ;
	}
	ret = process_tokens(lex);
	if (ret == -1)
		return (-1);
	lex->n_tokens += ret;
	return (lex->n_tokens);
}
