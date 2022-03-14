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

static int	wc_match_inner_loop(t_wcadd *wcadd, const char **wc,
								  const char **tgt)
{
	while (**tgt)
	{
		wcadd->swc = *wc;
		wcadd->stgt = *tgt;
		wcadd->ret = wc_match_fragment(wc, tgt, wcadd->tgt_end, &wcadd->st);
		if (wcadd->ret < 0)
			return (wcadd->ret);
		if (wcadd->ret > 0 && !**wc && *tgt != wcadd->tgt_end)
		{
			*tgt = wcadd->tgt_end - (*tgt - wcadd->stgt);
			*wc = wcadd->swc;
			return (wc_match_fragment(wc, tgt, wcadd->tgt_end, &wcadd->st));
		}
		if (wcadd->ret > 0)
			break ;
		(*tgt)++;
	}
	return (-1);
}

static int	wc_match_inner(const char *wc, const char *tgt)
{
	t_wcadd		wcadd;
	int			ret;

	if (wc_match_inner_init(&wcadd.st, &wc, &tgt, &wcadd.tgt_end) <= 0)
		return (0);
	while (*wc)
	{
		while (*wc == '*')
			wc++;
		if (!*wc)
			return (1);
		wcadd.ret = 0;
		ret = wc_match_inner_loop(&wcadd, &wc, &tgt);
		if (ret != -1)
			return (ret);
		if (wcadd.ret > 0)
			continue ;
		return (0);
	}
	return (tgt == wcadd.tgt_end);
}

int	wc_match(const char *wildcard, const char *target)
{
	return (wc_match_inner(wildcard, target));
}
