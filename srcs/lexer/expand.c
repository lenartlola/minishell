//
// Created by hypn0x on 3/13/22.
//

#include "../../incs/minishell.h"

static void	special_cases(char c, char **name, char **value)
{
	if (c == '?')
	{
		*name = ft_strdup("?");
		*value = ft_itoa(g_shell.lstatus);
	}
	else if (c == '=')
	{
		*name = ft_strdup("");
		*value = ft_strdup("$");
	}
}

static int	is_curly(t_expand *es, t_tkn *tkn)
{
	int	curly;

	curly = 0;
	if (tkn->data[es->end] == '{')
	{
		es->end++;
		if (tkn->data[es->end] == '}')
			return (print_error_ret("error: bad substitution\n", 1));
		curly = 1;
	}
	return (curly);
}

static int	get_name(t_expand *es, t_tkn *tkn, int *st)
{
	es->curly = is_curly(es, tkn);
	while (tkn->data[es->end] != '\0')
	{
		if (es->curly && !ft_isalnum(tkn->data[es->end])
			&& tkn->data[es->end] != '_' && tkn->data[es->end] != '}')
			return (print_error_ret("error: bad substitution\n", 1));
		if (*st == ST_GENERAL)
		{
			if (!ft_isalnum(tkn->data[es->end]) && tkn->data[es->end] != '_')
				break ;
		}
		else if (*st == ST_IN_DQUOTE)
		{
			if (!ft_isalnum(tkn->data[es->end]) && tkn->data[es->end] != '_')
				break ;
		}
		es->end++;
	}
	return (0);
}

static void	change_data(t_expand *es, t_tkn *tkn)
{
	char	*res;
	size_t	size;

	if (es->value == NULL)
		es->value = ft_strdup("");
	size = ft_strlen(tkn->data) - ft_strlen(es->name) + ft_strlen(es->value);
	size -= (es->curly * 2);
	res = (char *)ft_calloc(sizeof(char), size);
	if (res == NULL)
		print_error_ret("malloc", 1);
	ft_memcpy(res, tkn->data, es->start - 1);
	ft_strcat(res, es->value);
	ft_strcat(res,
			  tkn->data + es->start + ft_strlen(es->name) + (es->curly * 2));
	free(es->name);
	free(es->value);
	free(tkn->data);
	tkn->data = res;
}

int	expand(t_tkn *tkn, int *start, int st)
{
	t_expand	es;

	(*start)++;
	es.curly = 0;
	es.start = *start;
	es.end = *start;
	if (tkn->data[*start] == '?' || tkn->data[*start] == '=')
		special_cases(tkn->data[*start], &es.name, &es.value);
	else
	{
		get_name(&es, tkn, &st);
		if (es.curly == 1 && tkn->data[es.end] != '}')
			return (print_error_ret("error: bad substitution\n", 1));
		es.name = ft_substr(tkn->data, es.start + es.curly,
							es.end - es.start - es.curly);
		if (es.start + es.curly == es.end)
			es.value = ft_strdup("$");
		else
			es.value = ft_getenv(es.name);
	}
	*start -= 2;
	if (es.value != NULL)
		*start += ft_strlen(es.value);
	change_data(&es, tkn);
	return (0);
}