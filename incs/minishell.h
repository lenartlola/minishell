/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:35:03 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/18 12:13:19 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libs/libft/incs/libft.h"
# include <signal.h>
# include <termios.h>


typedef struct	s_shell
{
	char	*cmdline;
	char	**tokens;
	int		n_pipes;
	char	*cmds;
	char	**cmds_pipe[1024];
	char	*prompt;
}	t_shell;

void	tokenizing(t_shell *shell);
void	blocksig(int sig);
//parsing
int	parsing(t_shell *shell);
int fork_pipes (int n, char ***argv, char **env);
//prompt
void	init_prompt(t_shell *shell);

//exec
void	exec_path_cmd(char *path, t_shell *shell);
int	exec_pipe_cmd(t_shell *shell, char **env);

//piping
int	parse_pipes(t_shell *shell);

//Init ascii
void	init_shell(void);
#endif
