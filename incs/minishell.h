/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:35:03 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/16 09:36:52 by 1mthe0wl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libs/libft/incs/libft.h"

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
int	parsing(t_shell *shell);

//prompt
char	*init_prompt(void);

//exec
void	exec_path_cmd(char *path, t_shell *shell);
void	exec_pipe_cmd(t_shell *shell, char **env);

//piping
int	parse_pipes(t_shell *shell);
#endif
