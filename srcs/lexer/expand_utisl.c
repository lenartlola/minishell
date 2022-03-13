//
// Created by hypn0x on 3/13/22.
//

#include "../../incs/minishell.h"

static int	gen_st(t_tkn *tkn, int *st, int *len, int *i)
{
	if (tkn->data[*i] == CHAR_DL)
	{
		if (expand(tkn, i, *st))
			return (1);
		*len = ft_strlen(tkn->data);
	}
	else if (tkn->data[*i] == CHAR_QOUTE)
		*st = ST_IN_QUOTE;
	else if (tkn->data[*i] == CHAR_DQOUTE)
		*st = ST_IN_DQUOTE;
	return (0);
}

/* handle other states */
static int	other_st(t_tkn *tkn, int *st, int *len, int *i)
{
	if (*st == ST_IN_QUOTE)
	{
		if (tkn->data[*i] == CHAR_QOUTE)
			*st = ST_GENERAL;
	}
	else if (*st == ST_IN_DQUOTE)
	{
		if (tkn->data[*i] == CHAR_DL)
		{
			if (expand(tkn, i, *st))
				return (1);
			*len = ft_strlen(tkn->data);
		}
		else if (tkn->data[*i] == CHAR_DQOUTE)
			*st = ST_GENERAL;
	}
	return (0);
}

static int	re_lexer_build(t_tkn **tkn, t_tkn **prev,
							 t_lexer *lex, t_tknadd *ts)
{
	t_lexer	tmp;
	t_tkn	*aux;

	if (ft_strlen((*tkn)->data) <= 0)
	{
		ts->semaphore++;
		return (0);
	}
	else
	{
		if (tokenizing((*tkn)->data, ft_strlen((*tkn)->data), &tmp) <= 0)
		{
			lexer_del(&tmp);
			return (1);
		}
	}
	aux = tmp.tkn_list;
	ts->semaphore = 0;
	while (aux != NULL && ++ts->semaphore)
		aux = aux->next;
	insert_tknlst(tkn, prev, lex, tmp.tkn_list);
	return (0);
}

int	handle_expand(t_tkn **tkn, t_tkn **prev, t_lexer *lex, t_tknadd *ts)
{
	int		st;
	int		i;
	int		len;

	st = ST_GENERAL;
	len = ft_strlen((*tkn)->data);
	i = -1;
	while (i < len && (*tkn)->data[++i] != '\0')
	{
		if (st == ST_GENERAL)
			gen_st(*tkn, &st, &len, &i);
		else
			other_st(*tkn, &st, &len, &i);
	}
	return (re_lexer_build(tkn, prev, lex, ts));
}
