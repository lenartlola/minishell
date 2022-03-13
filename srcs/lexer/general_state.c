//
// Created by Hajar Sabir on 3/13/22.
//

//#include <minishell.h>
#include "../../incs/minishell.h"

static void	gst_quotes(t_lexadd *la)
{
	if (la->type == CHAR_QOUTE)
	{
		la->st = ST_IN_QUOTE;
		la->tkn->data[la->j++] = CHAR_QOUTE;
		la->tkn->type = TOK;
	}
	else if (la->type == CHAR_DQOUTE)
	{
		la->st = ST_IN_DQUOTE;
		la->tkn->data[la->j++] = CHAR_DQOUTE;
		la->tkn->type = TOK;
	}
	else if (la->type == CHAR_OCL)
	{
		la->st = ST_IN_CURLY;
		la->tkn->data[la->j++] = CHAR_OCL;
		la->tkn->type = TOK;
	}
}

static int	gst_esc(t_lexadd *la, const char *line)
{
	la->tkn->data[la->j++] = line[++la->i];
	la->tkn->type = TOK;
	return (0);
}

static int	gst_whitespace(t_lexadd *la, const size_t len)
{
	if (la->j > 0)
	{
		la->tkn->data[la->j] = 0;
		la->tkn->next = (t_tkn *)malloc(sizeof(t_tkn));
		if (la->tkn->next == NULL)
			print_error_ret("malloc", 1);
		la->tkn = la->tkn->next;
		if (tok_init(la->tkn, len - la->i))
			return (1);
		la->j = 0;
	}
	return (0);
}

static int	gst_special_chars(t_lexadd *la, const size_t len)
{
	if (la->j > 0)
	{
		la->tkn->data[la->j] = '\0';
		la->tkn->next = (t_tkn *)malloc(sizeof(t_tkn));
		if (!la->tkn->next)
			perror_ret("malloc", 1);
		la->tkn = la->tkn->next;
		if (tkn_init(la->tkn, len - la->i))
			return (1);
		la->j = 0;
	}
	la->tkn->data[0] = la->type;
	la->tkn->data[1] = '\0';
	la->tkn->type = la->type;
	la->tkn->next = (t_tkn *)malloc(sizeof(t_tkn));
	la->tkn = la->tkn->next;
	if (tkn_init(la->tkn, len - la->i))
		return (1);
	return (0);
}

int	handle_general_state(t_lexadd *la, const char *line, const size_t len)
{
	if (la->type == CHAR_QOUTE || la->type == CHAR_DQOUTE
		|| la->type == CHAR_OCL)
		gst_quotes(la);
	else if (la->type == CHAR_ESCSEQ)
		gst_esc(la, line);
	else if (la->type == CHAR_GEN)
	{
		la->tkn->data[la->j++] = la->c;
		la->tkn->type = TOK;
	}
	else if (la->type == CHAR_WS || la->type == CHAR_TAB)
	{
		if (gst_whitespace(la, len))
			return (1);
	}
	else if (la->type == CHAR_SC || la->type == CHAR_GT || la->type == CHAR_LS
			 || la->type == CHAR_AMP || la->type == CHAR_PIPE
			 || la->type == CHAR_OPR || la->type == CHAR_CPR)
	{
		if (gst_special_chars(la, len))
			return (1);
	}
	return (0);
}
