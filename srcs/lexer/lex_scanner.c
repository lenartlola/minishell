//
// Created by Hajar Sabir on 3/13/22.
//

#include "../../incs/minishell.h"

/*-----Demo scanner-----*/

/* print tokens */
static void print_tokens(t_lexer *lex)
{
	t_tkn *tmp;

	printf("------------------------------------\n");
	printf("n_tkn: %d\n", lex->n_tokens);
	tmp = lex->tkn_list;
	while (tmp)
	{
		printf("type: %d, data: %s\n", tmp->type, tmp->data);
		tmp = tmp->next;
	}
	printf("------------------------------------\n");
}

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
	if (ret <= 0)
	{
		if (ret == 0 && g_shell.tokdel == FALSE)
			write(STDERR_FILENO, "minish: syntax error\n", 20);
		free(g_shell.cmdline);
		g_shell.cmdline = NULL;
		lexer_del(&lex);
		return -1;
	}
	print_tokens(&lex);
	free(g_shell.cmdline);
	g_shell.cmdline = NULL;
	return (0);
}
