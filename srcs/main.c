/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:28:25 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/17 09:46:35 by 1mthe0wl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
	shell->cmdline = readline(shell->prompt);
	if (!(ft_strlen(shell->cmdline)))
	{
		free(shell->prompt);
		free(shell->cmdline);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	check_tty();
//	void(argc);
//	void(argv);
	init_shell();
	while (1)
	{
		signal(SIGQUIT, blocksig);
		signal(SIGINT, blocksig);
		init_line(&shell);
		if (!(ft_strncmp(shell.cmdline, "exit", 4)))
		{
			free(shell.prompt);
			free(shell.cmdline);
			//free(&shell);
			exit (EXIT_SUCCESS);
		}
		// We first take care about the pipes.
		tokenizing(&shell);
		parsing(&shell);
		//if (!(parsing(&shell)))
		//		continue ;
		if (shell.n_pipes)
			exec_pipe_cmd(&shell, env);
	}
	return (0);
}

void	blocksig(int sig)
{
	struct termios termios_new;
	int rc;

	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rc = tcgetattr(1, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(1, 0, &termios_new );
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
	}
		rl_replace_line("", 0);
		rl_redisplay();
}
