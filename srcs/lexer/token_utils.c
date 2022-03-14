//
// Created by Hajar Sabir on 3/13/22.
//

#include "../../incs/minishell.h"

int	tkn_init(t_tkn *tkn, size_t len)
{
	tkn->data = (char *)malloc((len + 2) * sizeof(char));
	if (tkn->data == NULL)
		print_error_ret("minish: failed to allocate memory\n", 1);
	tkn->data[0] = '\0';
	tkn->type = CHAR_NULL;
	tkn->next = NULL;
	return (0);
}

int	init_la(t_lexadd *la, t_lexer *lex, size_t len)
{
	lex->tkn_list = (t_tkn *)malloc(sizeof(t_tkn));
	if (!lex->tkn_list)
		return (print_error_ret("fatal error", 1));
	la->tkn = lex->tkn_list;
	tkn_init(la->tkn, len);
	la->st = ST_GENERAL;
	la->i = 0;
	la->j = 0;
	return (0);
}

void	del_node(t_tkn **tkn, t_tkn *prev)
{
	t_tkn	*tmp;

	if (prev == NULL)
	{
		tmp = *tkn;
		*tkn = (*tkn)->next;
		free(tmp->data);
		free(tmp);
	}
	else
	{
		tmp = *tkn;
		*tkn = (*tkn)->next;
		prev->next = *tkn;
		free(tmp->data);
		free(tmp);
	}
}

void	rejoin_tknens(t_tkn **tkn, t_tkn **prev, t_lexer *lex, t_tkn *head)
{
	int		cnt;
	t_tkn	*aux;

	aux = head;
	cnt = 1;
	while (aux->next && ++cnt)
		aux = aux->next;
	aux->next = (*tkn)->next;
	if (lex->tkn_list == *tkn)
		lex->tkn_list = head;
	else
		(*prev)->next = head;
	free((*tkn)->data);
	free(*tkn);
	lex->n_tokens += cnt;
	*tkn = aux->next;
	*prev = aux;
}
