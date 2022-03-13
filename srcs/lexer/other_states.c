//
// Created by Hajar Sabir on 3/13/22.
//

#include "../../incs/minishell.h"

void	handle_other_st(t_lexadd *la)
{
	if (la->st == ST_IN_QUOTE)
	{
		la->tkn->data[la->j++] = la->c;
		if (la->type == CHAR_QOUTE)
			la->st = ST_GENERAL;
	}
	else if (la->st == ST_IN_DQUOTE)
	{
		la->tkn->data[la->j++] = la->c;
		if (la->type == CHAR_DQOUTE)
			la->st = ST_GENERAL;
	}
	else if (la->st == ST_IN_CURLY)
	{
		la->tkn->data[la->j++] = la->c;
		if (la->type == CHAR_CCL)
			la->st = ST_GENERAL;
	}
}
