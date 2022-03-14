//
// Created by Hajar Sabir on 3/13/22.
//

#include "../../incs/minishell.h"

static void	swap_data(t_tkn *t1, t_tkn *t2)
{
	char	*tmp;

	tmp = t1->data;
	t1->data = t2->data;
	t2->data = tmp;
}

static int	lowercmp(const char *s1, const char *s2)
{
	int	c1;
	int	c2;

	while (*s1 != '\0' && *s2 != '\0' && ft_tolower(*s1) == ft_tolower(*s2))
	{
		s1++;
		s2++;
	}
	c1 = (unsigned char)ft_tolower(*s1);
	c2 = (unsigned char)ft_tolower(*s2);
	if (ft_islower(c1))
		c1++;
	if (ft_islower(c2))
		c2++;
	if (c1 == '~')
		c1 = 'a';
	if (c2 == '~')
		c2 = 'a';
	return (c1 - c2);
}

void	sort_list(t_tkn **head)
{
	t_tkn	*aux1;
	t_tkn	*aux2;

	aux1 = *head;
	while (aux1)
	{
		aux2 = aux1->next;
		while (aux2)
		{
			if (lowercmp(aux1->data, aux2->data) > 0)
				swap_data(aux1, aux2);
			aux2 = aux2->next;
		}
		aux1 = aux1->next;
	}
}

void	read_dir(t_tkn **head, DIR *ls, struct dirent *list)
{
	t_tkn	*aux;

	aux = *head;
	while (list)
	{
		aux->data = ft_strdup(list->d_name);
		aux->type = TOK;
		list = readdir(ls);
		if (list)
		{
			aux->next = (t_tkn *)ft_calloc(1, sizeof(t_tkn));
			aux = aux->next;
		}
	}
	aux->next = NULL;
	sort_list(head);
}

static void	handle_quotes(int *st, char **wc, t_bool *incr)
{
	if (*st == ST_GENERAL && (**wc == CHAR_QOUTE || **wc == CHAR_DQOUTE))
	{
		if (**wc == CHAR_QOUTE)
			*st = ST_IN_QUOTE;
		else if (**wc == CHAR_DQOUTE)
			*st = ST_IN_DQUOTE;
		(*wc)++;
		*incr = TRUE;
	}
}

int	wc_check(t_tkn *tkn)
{
	int		st;
	t_bool	incr;
	char	*wc;

	if (tkn->data == NULL)
		return (1);
	st = ST_GENERAL;
	wc = tkn->data;
	while (*wc != '\0')
	{
		incr = FALSE;
		handle_quotes(&st, &wc, &incr);
		if (*wc != '\0' && ((st == ST_IN_QUOTE && *wc == CHAR_QOUTE)
							|| (st == ST_IN_DQUOTE && *wc == CHAR_DQOUTE)))
		{
			incr = TRUE;
			st = ST_GENERAL;
			wc++;
		}
		if (st == ST_GENERAL && (*wc == '?' || *wc == '*'))
			return (1);
		if (incr == FALSE)
			wc++;
	}
	return (0);
}
