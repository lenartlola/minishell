//
// Created by Hajar Sabir on 3/13/22.
//

#include "../../incs/minishell.h"

static int	check_line(char *line)
{
	char	*aux;

	if (line == NULL || *line == '\0' || *line == '\n')
	{
		free_struct();
		return (1);
	}
	aux = line;
	while (*aux != '\0')
	{
		if (ft_isblank(*aux) == 0)
			break ;
		aux++;
	}
	if (*aux == '\0')
	{
		free_struct();
		return (1);
	}
	return (0);
}


int	handle_line()
{
	t_lexer	lex;
	t_ast	*ast;
	int		ret;

	ast = NULL;
	if (check_line(g_shell.cmdline) == 1)
		return (-1);
	ret = tokenizing(g_shell.cmdline, ft_strlen(g_shell.cmdline), &lex);
	//TODO: Error handling.
	// Maybe tomorrow, I'm so fucking tired
}
