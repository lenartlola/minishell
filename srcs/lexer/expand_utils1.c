//
// Created by hypn0x on 3/13/22.
//

#include "../../incs/minishell.h"

void	tok_del(t_tkn *tkn)
{
	if (tkn != NULL)
	{
		free(tkn->data);
		tok_del(tkn->next);
		free(tkn);
	}
}

void	lexer_del(t_lexer *lex)
{
	if (lex == NULL)
		return ;
	tok_del(lex->tkn_list);
}

void	insert_tknlst(t_tkn **tkn, t_tkn **prev, t_lexer *lex, t_tkn *head)
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
	*tkn = head;
}