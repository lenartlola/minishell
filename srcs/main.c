/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:28:25 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/16 21:24:23 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_shell(void)
{
	printf("%s⡆⣐⢕⢕⢕⢕⢕⢕⢕⢕⠅⢗⢕⢕⢕⢕⢕⢕⢕⠕⠕⢕⢕⢕⢕⢕⢕⢕⢕⢕\n", KCYN);
	printf("⢐⢕⢕⢕⢕⢕⣕⢕⢕⠕⠁⢕⢕⢕⢕⢕⢕⢕⢕⠅%s⡄%s⢕⢕⢕⢕⢕⢕⢕⢕⢕\n", KNRM, KCYN);
	printf("⢕⢕⢕⢕⢕⠅⢗⢕⠕%s⣠⠄%s⣗⢕⢕⠕⢕⢕⢕⠕%s⢠⣿%s⠐⢕⢕⢕⠑⢕⢕⠵⢕\n", KNRM, KCYN, KNRM, KCYN);
	printf("⢕⢕⢕⢕⠁⢜⠕%s⢁⣴⣿⡇%s⢓⢕⢵⢐⢕⢕⠕%s⢁⣾⢿⣧%s⠑⢕⢕⠄⢑⢕⠅⢕\n", KNRM, KCYN, KNRM, KCYN);
	printf("⢕⢕⠵⢁⠔%s⢁⣤⣤⣶⣶⣶%s⡐⣕⢽⠐⢕⠕%s⣡⣾⣶⣶⣶⣤⡁%s⢓⢕⠄⢑⢅⢑\n", KNRM, KCYN, KNRM, KCYN);
	printf("⠍⣧⠄%s⣶⣾⣿⣿⣿⣿⣿⣿⣷⣔%s⢕⢄⢡%s⣾⣿⣿⣿⣿⣿⣿⣿⣦⡑⢕⢤⠱%s⢐\n", KNRM, KCYN, KNRM, KCYN);
	printf("⢠⢕⠅%s⣾⣿⠋⢿⣿⣿⣿⠉⣿⣿⣷⣦⣶⣽⣿⣿⠈⣿⣿⣿⣿⠏⢹⣷⣷⡅%s⢐\n", KNRM, KCYN);
	printf("⣔⢕⢥%s⢻⣿⡀⠈⠛⠛⠁⢠⣿⣿⣿⣿⣿⣿⣿⣿⡀⠈⠛⠛⠁⠄⣼⣿⣿⡇%s⢔\n", KNRM, KCYN);
	printf("⢕⢕⢽%s⢸⢟⢟%s⢖⢖%s⢤⣶⡟⢻⣿⡿⠻⣿⣿⡟⢀⣿⣦%s⢤⢤⢔%s⢞⢿⢿⣿⠁%s⢕\n", KNRM, KMAG, KNRM, KMAG, KNRM, KCYN);
	printf("⢕⢕⠅%s⣐⢕⢕⢕⢕⢕%s⣿⣿⡄⠛⢀⣦⠈⠛⢁⣼⣿%s⢗⢕⢕⢕⢕⢕⢕⡏%s⣘⢕\n", KMAG, KNRM, KMAG, KCYN);
	printf("⢕⢕⠅%s⢓⣕⣕⣕⣕%s⣵⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣷%s⣕⢕⢕⢕⢕⡵%s⢀⢕⢕\n", KMAG, KNRM, KMAG, KCYN);
	printf("⢑⢕⠃%s⡈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃%s⢕⢕⢕\n", KNRM, KCYN);
	printf("⣆⢕⠄⢱⣄%s⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢁%s⢕⢕⠕⢁\n", KNRM, KCYN);
	printf("⣿⣦⡀⣿⣿⣷⣶⣬⣍%s⣛⣛⣛⡛⠿⠿⠿⠛⠛⢛⣛⣉⣭%s⣤⣂⢜⠕⢑⣡⣴⣿%s\n", KNRM, KCYN, KNRM);
	printf("\n");
	printf("-----------------------------------------------------------------------\n");
	printf("\n");
	printf("%s", KRED);
	printf("              $$\\           $$\\           $$\\                 $$\\ $$\\ \n");
	printf("              \\__|          \\__|          $$ |                $$ |$$ |\n");
	printf("$$$$$$\\$$$$\\  $$\\ $$$$$$$\\  $$\\  $$$$$$$\\ $$$$$$$\\   $$$$$$\\  $$ |$$ |\n");
	printf("%s$$  _$$  _$$\\ $$ |$$  __$$\\ $$ |$$  _____|$$  __$$\\ $$  __$$\\ $$ |$$ |\n", KMAG);
	printf("%s$$ / $$ / $$ |$$ |$$ |  $$ |$$ |\\$$$$$$\\  $$ |  $$ |$$$$$$$$ |$$ |$$ |\n", KYEL);
	printf("%s$$ | $$ | $$ |$$ |$$ |  $$ |$$ | \\____$$\\ $$ |  $$ |$$   ____|$$ |$$ |\n", KGRN);
	printf("%s$$ / $$ / $$ |$$ |$$ |  $$ |$$ |\\$$$$$$\\  $$ |  $$ |$$$$$$$$ |$$ |$$ |\n", KCYN);
	printf("%s$$ | $$ | $$ |$$ |$$ |  $$ |$$ |$$$$$$$  |$$ |  $$ |\\$$$$$$$\\ $$ |$$ |\n", KBLU);
	printf("%s\\__| \\__| \\__|\\__|\\__|  \\__|\\__|\\_______/ \\__|  \\__| \\_______|\\__|\\__|\n", KWHT);
	printf("\n");
	printf("%s", KNRM);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (argc > 1)
		printf("It is a shell, therefore it doesn't require any aargument");
	init_shell();
	while (1)
	{
		signal(SIGQUIT, blocksig);
		signal(SIGINT, blocksig);
		shell.prompt = init_prompt();
		shell.cmdline = readline(shell.prompt);
		if (!(ft_strlen(shell.cmdline)))
		{
			free(shell.prompt);
			free(shell.cmdline);
			continue ;
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
