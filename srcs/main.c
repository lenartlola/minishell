/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:28:25 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/18 16:32:42 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int a = 0;

void	check_tty()
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		printf("/!\\ forbidden action detected");
		exit(EXIT_FAILURE);
	}
}

void	init_line(t_shell *shell)
{
	init_prompt(shell);
	signal(SIGQUIT, SIG_IGN);
	rl_replace_line("",0);
	shell->cmdline = readline(shell->prompt);
	if (!shell->cmdline)
	{
		free_struct(shell);
		rl_clear_history();
		exit (EXIT_SUCCESS);
	}
	a++;
	while (!(ft_strlen(shell->cmdline)))
	{
		free(shell->prompt);
		free(shell->cmdline);
		init_line(shell);
	} 
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	check_tty();
	init_shell();
	shell.cmdline = NULL;
	while (1)
	{
		a = 0;
		signal(SIGINT, blocksig);
		init_line(&shell);
		if (shell.cmdline && !(ft_strncmp(shell.cmdline, "exit", 4)))
		{
			free_struct(&shell);
			rl_clear_history();
			exit (EXIT_SUCCESS);
		}
		if (shell.cmdline)
		{
			add_history(shell.cmdline);
			tokenizing(&shell);
			parsing(&shell);
			if (shell.n_pipes)
			{
				if (shell.pipe_flag == 1)
					exec_pipe_cmd(&shell, env);
				else if (shell.pipe_flag == 0)
					printf("minishell: syntax error near unexpected token `%s'\n", shell.cmdline);
			}
		}
	}
	free_struct(&shell);
	return (0);
}

void	blocksig(int sig)
{
	struct termios termios_new;
	int rc;
	
	rc = tcgetattr(1, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(1, 0, &termios_new );
	if (a == 0)		
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
}
