/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:28:25 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/23 15:38:13 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char **g_env = NULL;

/*
 * Init a nice prompt, Init a new line, 
 * wait to user promt. verify if there is some strings
 * otherwise free the allocated memory and reinit.
 */

void	init_line(t_shell *shell)
{
	if (!shell->cmdline)
		init_prompt(shell);
	signal(SIGQUIT, SIG_IGN);
	rl_replace_line("",0);
	shell->cmdline = readline(shell->prompt);
	if (!shell->cmdline)
	{
		if (shell->cmdline != NULL)
			free_struct(shell);
		rl_clear_history();
		exit (EXIT_SUCCESS);
	}
	while (!(ft_strlen(shell->cmdline)))
	{
		free(shell->cmdline);
		init_line(shell);
	} 
}

/*
 * The core of the program.
 * Init a shell structure with some utilities, refer to minishell.h
 * if cmdline is exit and no more strings exist, free the allocated
 * memory and leave the program.
 * if some strings are given then add a history and pass to tokenizing part.
 */

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

//	check_tty();
	init_shell();
	shell.cmdline = NULL;
	shell.ev = ft_calloc(sizeof(env), 100);
	shell.ev = env;
	while (1)
	{
		g_env = NULL;
		signal(SIGINT, (void (*)(int))blocksig);
		init_line(&shell);
		if (shell.cmdline && !(ft_strncmp(shell.cmdline, "exit", 4)) && ft_strlen(shell.cmdline) == 4)
		{
			free_struct(&shell);
			rl_clear_history();
			exit (EXIT_SUCCESS);
		}
		if (shell.cmdline)
		{
			g_env = env;
			add_history(shell.cmdline);
			if (tokenizing(&shell) == -1)
				continue ;
			if (*shell.cmd->token)
			{	//printf("Hello cmd %s\n", shell.cmd->token[0]);
				parsing(&shell);
			}
			if (shell.n_pipes)
			{
				if (shell.pipe_flag == 1)
					exec_pipe_cmd(&shell, env);
				else if (shell.pipe_flag == 0)
					printf("minishell: syntax error near unexpected token `%s'\n", shell.cmdline);
			}
		}
		//free(shell.cmdline);
	}
	free_struct(&shell);
	return (0);
}

void	blocksig(const int sig, void *ptr)
{
	struct termios termios_new;
	static int a;
	int rc;
	
	a = 0;
	rc = tcgetattr(1, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(1, 0, &termios_new );
	if (!g_env) 
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
//		shell->cmdline = NULL;
	}
}
