/**
 * @author      : hypn0x (wubbalubba@dubdub)
 * @file        : init_shell
 * @created     : Sunday Mar 13, 2022 11:13:47 CET
 */

#include "../incs/minishell.h"

//static void	add_bltn(t_bltin **head, char *name, int (*f)(char **))
//{
//	t_bltin	*new;
//	t_bltin	*aux;
//
//	new = (t_bltin *)malloc(sizeof(t_bltin));
//	if (new == NULL)
//		print_error("malloc");
//	new->name = name;
//	new->f = f;
//	new->next = NULL;
//	if (*head != NULL)
//	{
//		aux = *head;
//		while (aux->next)
//			aux = aux->next;
//		aux->next = new;
//	}
//	else
//		*head = new;
//}
//
//static t_bltin	*init_bltn(void)
//{
//	t_bltin	*bln;
//
//	bln = NULL;
//	add_bltn(&bln, "echo", ft_echo);
//	add_bltn(&bln, "cd", ft_cd);
//	add_bltn(&bln, "pwd", ft_pwd);
//	add_bltn(&bln, "export", ft_export);
//	add_bltn(&bln, "unset", ft_unset);
//	add_bltn(&bln, "env", ft_env);
//	return (bln);
//}

static void	init_vars(void)
{
	g_shell.lstatus = EXIT_SUCCESS;
//	g_shell.builtin = init_bltn();
	g_shell.cmdline = NULL;
	g_shell.is_expd = FALSE;
	//g_shell->ret = 0;
	g_shell.std_in = 0;
	g_shell.std_out = 0;
}

void	init_shell(void)
{
	extern char	**environ;

	fill_envs(environ);
	init_ascii();
	init_vars();
	parrent_handler();
}
