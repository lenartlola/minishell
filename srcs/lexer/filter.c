//
// Created by Hajar Sabir on 3/13/22.
//

#include <minishell.h>

int	get_ctype(char c)
{
	if (c == '\'')
		return (CHAR_QOUTE);
	else if (c == '\"')
		return (CHAR_DQOUTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '&')
		return (CHAR_AMP);
	else if (c == ' ')
		return (CHAR_WS);
	else if (c == ';')
		return (CHAR_SC);
	else if (c == '\\')
		return (CHAR_ESCSEQ);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NL);
	else if (c == '>')
		return (CHAR_GT);
	else if (c == '<')
		return (CHAR_LS);
	else if (c == '\0')
		return (CHAR_NULL);
	return (get_ctype_2(c));
}
