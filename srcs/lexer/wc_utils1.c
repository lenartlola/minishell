//
// Created by Hajar Sabir on 3/13/22.
//

#include "../../incs/minishell.h"

static int	wc_match_inner_init(int *st, const char **wc,
								  const char **tgt, const char **tgt_end)
{
	int	ret;

	*st = ST_GENERAL;
	*tgt_end = *tgt + ft_strlen(*tgt);
	if (**wc != '*')
	{
		ret = wc_match_fragment(wc, tgt, *tgt_end, st);
		if (ret <= 0)
			return (ret);
	}
	return (1);
}

static int	wc_match_inner_loop(t_wcsup *wcsup, const char **wc,
								  const char **tgt)
{
	while (**tgt)
	{
		wcsup->swc = *wc;
		wcsup->stgt = *tgt;
		wcsup->ret = wc_match_fragment(wc, tgt, wcsup->tgt_end, &wcsup->st);
		if (wcsup->ret < 0)
			return (wcsup->ret);
		if (wcsup->ret > 0 && !**wc && *tgt != wcsup->tgt_end)
		{
			*tgt = wcsup->tgt_end - (*tgt - wcsup->stgt);
			*wc = wcsup->swc;
			return (wc_match_fragment(wc, tgt, wcsup->tgt_end, &wcsup->st));
		}
		if (wcsup->ret > 0)
			break ;
		(*tgt)++;
	}
	return (-1);
}

static int	wc_match_inner(const char *wc, const char *tgt)
{
	t_wcsup		wcsup;
	int			ret;

	if (wc_match_inner_init(&wcsup.st, &wc, &tgt, &wcsup.tgt_end) <= 0)
		return (0);
	while (*wc)
	{
		while (*wc == '*')
			wc++;
		if (!*wc)
			return (1);
		wcsup.ret = 0;
		ret = wc_match_inner_loop(&wcsup, &wc, &tgt);
		if (ret != -1)
			return (ret);
		if (wcsup.ret > 0)
			continue ;
		return (0);
	}
	return (tgt == wcsup.tgt_end);
}

int	wc_match(const char *wildcard, const char *target)
{
	return (wc_match_inner(wildcard, target));
}
