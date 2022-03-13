//
// Created by Hajar Sabir on 3/13/22.
//

#include "../../incs/minishell.h"

static t_tkn	*create_list(void)
{
	t_tkn			*head;
	DIR				*ls;
	char			*cwd;
	struct dirent	*list;

	cwd = malloc(sizeof(char) * PATH_MAX);
	if (!cwd)
		return (NULL);
	if (!getcwd(cwd, PATH_MAX))
		return (NULL);
	ls = opendir(cwd);
	free(cwd);
	head = (t_tkn *)ft_calloc(1, sizeof(t_tkn));
	if (head == NULL)
		return (NULL);
	list = readdir(ls);
	read_dir(&head, ls, list);
	closedir(ls);
	return (head);
}

static int	del_hidden_files(t_tkn **head)
{
	t_tkn 	*aux;
	t_tkn	*prev;

	aux = *head;
	while (aux)
	{
		if (ft_strncmp((char *)aux->data, ".", 1) == 0)
		{
			if (aux == *head)
			{
				del_node(head, NULL);
				aux = *head;
			}
			else
				del_node(&aux, prev);
			continue ;
		}
		prev = aux;
		aux = aux->next;
	}
	return (0);
}

static void	match(t_tkn **head, const char *wildcard)
{
	t_tkn	*aux;
	t_tkn	*prev;

	prev = NULL;
	aux = *head;
	while (aux != NULL)
	{
		if (wc_match(wildcard, aux->data) <= 0)
		{
			if (aux == *head)
			{
				del_node(head, NULL);
				aux = *head;
			}
			else
				del_node(&aux, prev);
			continue ;
		}
		prev = aux;
		aux = aux->next;
	}
}

int	handle_wildcards(t_tkn **tkn, t_tkn **prev, t_lexer *lex)
{
	t_tkn	*head;

	if (wc_check(*tkn) == 0)
		return (0);
	head = create_list();
	if (head == NULL)
		return (-1);
	if (ft_strncmp((*tkn)->data, ".", 1))
		del_hidden_files(&head);
	match(&head, (*tkn)->data);
	if (head == NULL)
		return (0);
	if (head->next != NULL && g_shell.prev
		&& (g_shell.prev->type == CHAR_GT || g_shell.prev->type == CHAR_LS))
	{
		wc_put_error(tkn, head);
		return (-1);
	}
	rejoin_tknens(tkn, prev, lex, head);
	return (1);
}
