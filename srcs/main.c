/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:28:25 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/05 14:26:35 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//int	*g_ptr;
/*
 * Init a nice prompt, Init a new line, 
 * wait to user promt. verify if there is some strings
 * otherwise free the allocated memory and reinit.
 */

void	init_line(t_shell *shell)
{
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
 * Init a shell structure with some utilities, refer to "minishell.h".
 * if cmdline is exit and no more strings exist, free the allocated
 * memory and leave the program.
 * if some strings are given then add a history and pass to tokenizing part.
 */

void	init_shell(t_shell *shell, char **env)
{
	shell->cmdline = NULL;
	if (!g_env)
		shell->env = get_envs(env);
	g_env = shell->env;
	shell->cmd = NULL;
	shell->ret = 0;
	shell->lreturn = 0;
	shell->std_in = 0;
	shell->std_out = 0;
	tcgetattr(0, &shell->term);
	//g_ptr = &shell->ret;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	init_ascii();
	//init_shell(&shell, env);
	while (1)
	{
		init_shell(&shell, env);
		parrent_handler();
		init_line(&shell);
		if (shell.cmdline && !(ft_strncmp(shell.cmdline, "exit", ft_strlen(shell.cmdline))))
		{
			free_struct(&shell);
			free_envs(shell.env);
//			if (shell.prompt)
//				free(shell.prompt);
			printf("exit\n");
			rl_clear_history();
			exit (EXIT_SUCCESS);
		}
		if (shell.cmdline)
		{
			add_history(shell.cmdline);
			if (tokenizing(&shell) == -1)
				continue ;
			if (*shell.cmd->token || *shell.cmd->redirection)
			{
				parsing(&shell, env);
			}
			else if (shell.cmd)
			{
				free_cmd(shell.cmd);
				shell.cmd = NULL;
			}
		}
		free(shell.prompt);
		shell.prompt = NULL;
//		free_envs(shell.env);
	}
	return (0);
}
/*
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
}*/
