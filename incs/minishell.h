/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:35:03 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/16 21:20:09 by hsabir           ###   ########.fr       */
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

# define READ_END 0
# define WRITE_END 1

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

//parsing
char	*parsing(t_shell *shell);

//prompt
char	*init_prompt(void);

//exec
void	exec_path_cmd(char *path, t_shell *shell);
void	exec_pipe_cmd(char	*path, t_shell *shell);

char	*check_cmd(char *cmd, t_shell *shell);
//piping
int	parse_pipes(t_shell *shell);

//check cmd
char	*check_cmd_pipe(char *cmd);
#endif
