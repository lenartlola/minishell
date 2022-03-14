/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:28:25 by hsabir            #+#    #+#             */
/*   Updated: 2022/03/14 13:59:36 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//t_env	*g_env;
t_shell	g_shell;

//get_line(char *line)
//{
//	init_prompt();
//	signal(SIGQUIT, SIG_IGN);
//	rl_replace_line("", 0);
//	rl_redisplay();
//
//	g_shell.cmdline = readline(g_shell.prompt);
//	if (!g_shell.cmdline)
//	{
//		if (g_shell.cmdline != NULL)
//			free_struct();
//		rl_clear_history();
//		exit (EXIT_SUCCESS);
//	}
//	while (!(ft_strlen(g_shell.cmdline)))
//	{
//		free(g_shell.cmdline);
//		g_shell.cmdline = NULL;
//		get_line(line);
//	}
//	line = g_shell.cmdline;
//}

void	init_line()
{
	init_prompt(g_shell);
	signal(SIGQUIT, SIG_IGN);
	rl_replace_line("", 0);
	rl_redisplay();
	g_shell.cmdline = readline(g_shell.prompt);
	if (!g_shell.cmdline)
	{
		if (g_shell.cmdline != NULL)
			free_struct();
		rl_clear_history();
		exit (EXIT_SUCCESS);
	}
	while (!(ft_strlen(g_shell.cmdline)))
	{
		free_struct();
		init_line();
	}
}


void	ft_exit()
{
	free_struct();
//	free_envs(shell->env);
	printf("exit\n");
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

static void	check_isatty(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		exit(EXIT_FAILURE);
	}
}

//void	init_shell(t_shell *shell, char **env)
//{
//	parrent_handler();
//	shell->cmdline = NULL;
//	if (!g_env)
//		shell->env = get_envs(env);
//	g_env = shell->env;
//	shell->cmd = NULL;
//	shell->ret = 0;
//	shell->std_in = 0;
//	shell->std_out = 0;
//	tcgetattr(0, &shell->term);
//	init_line(shell);
//}

int	main(int argc, char **argv)
{
//	t_shell	shell;
//	char 	*line;

	check_isatty(argc, argv);
	init_shell();
	while (1)
	{
		parrent_handler();
		g_shell.is_expd = FALSE;
		init_line();
		if (g_shell.cmdline && !(ft_strncmp(g_shell.cmdline,
					"exit", ft_strlen(g_shell.cmdline))))
			ft_exit();
		if (g_shell.cmdline)
		{
			add_history(g_shell.cmdline);
			if (handle_line() == -1)
				continue ;
			//if (tokenizing(&shell) == -1)
			//	continue ;
			//if (*shell.cmd->token || *shell.cmd->redirection)
			//	parsing(&shell, env);
			//else if (shell.cmd)
			//{
			//	free_cmd(shell.cmd);
			//	shell.cmd = NULL;
			//}
		}
		free_struct();
	}
	return (EXIT_SUCCESS);
}
