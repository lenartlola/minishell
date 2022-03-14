//
// Created by Hajar Sabir on 3/14/22.
//

#include "../../incs/minishell.h"

static const char	*handle_quotes(int *st, const char *f)
{
	if (*st == ST_GENERAL && (*f == CHAR_QOUTE || *f == CHAR_DQOUTE))
	{
		if (*f == CHAR_QOUTE)
			*st = ST_IN_QUOTE;
		else if (*f == CHAR_DQOUTE)
			*st = ST_IN_DQUOTE;
		f++;
	}
	return (f);
}

static int	wc_match_fragment_qmark(const char **f, const char **t, int *st)
{
	if (**f == '?' && *st == ST_GENERAL)
		(*f)++;
	else
	{
		if (**f != **t)
			return (0);
		(*f)++;
	}
	return (1);
}

static void	wc_match_fragment_end(const char **frag, const char **tgt,
									 const char *f, const char *t)
{
	*frag = f;
	*tgt = t;
}

int	wc_match_fragment(const char **frag, const char **tgt,
						 const char *tgt_end, int *st)
{
	const char	*f;
	const char	*t;

	f = *frag;
	t = *tgt;
	while (*f && (*f != '*' || *st != ST_GENERAL) && t < tgt_end)
	{
		f = handle_quotes(st, f);
		if ((*st == ST_IN_QUOTE && *f == CHAR_QOUTE)
			|| (*st == ST_IN_DQUOTE && *f == CHAR_DQOUTE))
		{
			*st = ST_GENERAL;
			if (*(++f) == '*')
				break ;
		}
		if (wc_match_fragment_qmark(&f, &t, st) == 0)
			return (0);
		t++;
	}
	if (!*f || (*f == '*' && *st == ST_GENERAL))
	{
		wc_match_fragment_end(frag, tgt, f, t);
		return (1);
	}
	return (0);
}
