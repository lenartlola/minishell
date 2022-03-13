//
// Created by Hajar Sabir on 3/13/22.
//

#include "../../incs/minishell.h"

static int	handle_wildcard(t_lexer *lex, t_tknadd *ta)
{
	int		ret;

	if (ta->semaphore == 0 && g_shell.is_expd == FALSE)
	{
		g_shell.is_expd = TRUE;
		g_shell.prev = ta->prev;
		ret = handle_expand(&ta->aux, &ta->prev, lex, ta);
		g_shell.is_expd = FALSE;
		if (ret == 1)
			return (-1);
		if (check_tok(lex, &ta->aux, ta->prev))
		{
			g_shell.tokdel = TRUE;
			return (1);
		}
	}
	if (ta->semaphore > 0 && g_shell.is_expd == FALSE)
		ta->semaphore--;
	ret = handle_wildcards(&ta->aux, &ta->prev, lex);
	if (ret == -1)
		return (-1);
	else if (ret == 1)
		return (1);
	return (5);
}

static int	handle_token(t_lexer *lex, t_tknadd *ta)
{
	char	*trimed;
	int		ret;

	if (ta->is_heredoc == 0)
	{
		ret = handle_wildcard(lex, ta);
		if (ret != 5)
			return (ret);
	}
	if (g_shell.is_expd == FALSE)
	{
		trimed = (char *)malloc(ft_strlen(ta->aux->data) + 1);
		if (trimed == NULL)
			return (perror_ret("malloc", -1));
		trim_quotes(trimed, ta->aux->data);
		free(ta->aux->data);
		ta->aux->data = trimed;
	}
	ta->cnt++;
	return (2);
}

static int	parse_tokens(t_tkn *tkn, t_tkn *prev, t_lexer *lex, t_tknadd *ta)
{
	int			ret;

	ta->aux = tkn;
	ta->prev = prev;
	ta->is_heredoc = 0;
	ta->cnt = 0;
	ta->semaphore = 0;
	while (ta->aux)
	{
		if (ta->aux->type == TOK)
		{
			ret = handle_token(lex, ta);
			if (ret <= 0)
				return (ret);
			else if (ret == 1)
				continue ;
		}
		if (ta->prev && ta->prev->type == CHAR_LS && ta->aux->type == CHAR_LS)
			ta->is_heredoc = 1;
		else
			ta->is_heredoc = 0;
		ta->prev = ta->aux;
		ta->aux = ta->aux->next;
	}
	return (ta->cnt);
}

int	process_tokens(t_lexer *lex)
{
	t_tknadd 	ta;
	t_tkn		*tok;
	t_tkn		*prev;
	int			cnt;

	prev = NULL;
	tkn = lex->tkn_list;
	cnt = parse_tokens(tok, prev, lex, &ta);
	return (cnt);
}
