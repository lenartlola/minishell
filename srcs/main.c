/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:28:25 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/17 22:20:25 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
int a = 0;
void	check_tty()
{
//	void(argc);
//	void(argv);
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		printf("/!\\ forbidden action detected");
		exit(EXIT_FAILURE);
	}
}

void	init_line(t_shell *shell)
{
	shell->prompt = init_prompt();
	signal(SIGQUIT, SIG_IGN);
	rl_replace_line("",0);
	shell->cmdline = readline(shell->prompt);
	if (!shell->cmdline)
	{
		free(shell->prompt);
		free(shell->cmdline);
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
//	void(argc);
//	void(argv);
	init_shell();
	shell.cmdline = NULL;
	while (1)
	{
		a = 0;
		signal(SIGINT, blocksig);
		init_line(&shell);
		if (shell.cmdline && !(ft_strncmp(shell.cmdline, "exit", 4)))
		{
			free(shell.prompt);
			free(shell.cmdline);
			rl_clear_history();
			exit (EXIT_SUCCESS);
		}
		// We first take care about the pipes.
		if (shell.cmdline)
		{
			add_history(shell.cmdline);
			tokenizing(&shell);
			parsing(&shell);
		//if (!(parsing(&shell)))
		//		continue ;
			if (shell.n_pipes)
				exec_pipe_cmd(&shell, env);
		}
	}
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
