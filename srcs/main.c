/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:28:25 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/16 14:28:42 by hsabir           ###   ########.fr       */
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
	printf("⣿⣦⡀⣿⣿⣷⣶⣬⣍%s⣛⣛⣛⡛⠿⠿⠿⠛⠛⢛⣛⣉⣭%s⣤⣂⢜⠕⢑⣡⣴⣿%s\n", KNRM, KCYN);
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
		shell.prompt = init_prompt();
		shell.cmdline = readline(shell.prompt);
		if (!ft_strlen(shell.cmdline))
		{
			free(shell.prompt);
			free(shell.cmdline);
			continue ;
		}
		// We first take care about the pipes.
		tokenizing(&shell);
		if (!(parsing(&shell)))
				continue ;
		if (shell.n_pipes && shell.n_pipes == 1)
			exec_pipe_cmd(&shell, env);
	}
	return (0);
}
