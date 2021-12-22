/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:35:03 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/22 16:21:12 by hsabir           ###   ########.fr       */
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

extern char **g_env;

typedef struct s_quotes	t_quotes;
typedef struct s_cmd	t_cmd;

typedef enum	s_type
{
	SIMPLE,
	DOUBLE,
	NONE,
}	t_type;

typedef struct	s_quotes
{
	int	start;
	int	end;
	t_type	type;
	t_quotes	*next;
}	t_quotes;

typedef struct	s_vars
{
	t_cmd		*cmd;
	t_quotes	*quotes;
	char		*str;
}	t_vars;

typedef struct	s_cmd
{
	char	**token;
	t_cmd	*next;
}	t_cmd;

typedef struct	s_shell
{
	t_cmd	*cmd;
	char	*cmdline;
	char	**tokens;
	int		n_pipes;
	int		pipe_flag;
	int		pipe_cmd_exist;
	char	*cmds;
	char	**cmds_pipe[1024];
	char	*prompt;
	char	**ev;
	char	**exp;
}	t_shell;

void	tokenizing(t_shell *shell);
void	blocksig(int sig, void *ptr);
//parsing
int	parsing(t_shell *shell);
int fork_pipes (int n, char ***argv, char **env);
//prompt
void	init_prompt(t_shell *shell);

//exec
void	exec_path_cmd(char *path, t_shell *shell);
int		exec_pipe_cmd(t_shell *shell, char **env);

//piping
int	parse_pipes(t_shell *shell);
//builtin
int	ft_env(t_shell *shell);
int	ft_echo(char **cmd);
int     ft_cd(char **cmd, t_shell *shell);
int	ft_export(char **cmd, t_shell *shell);
//Init ascii
void	init_shell(void);
//Free
void	free_struct(t_shell *shell);
int		double_free(char **array);
//Error
void	print_error(char *str);

//char	**g_env;

//quotes/
int	parse_simple_quote(t_vars *vars, t_cmd *current, int i);
int	parse_double_quote(t_vars *vars, t_cmd *current, int i);
int	ft_strhas(char *str, char *set);
void	set_quotes_data(t_vars *vars, t_quotes *quotes, t_quotes tmp);
void	parse_quotes(t_vars *vars, int len);
int	quotes_error();

//str_utils
int		get_c_index(char *str, char c);
int		trim_spaces(char *str);
int		is_sep(char c);
int		quote_counter(t_vars *vars, int start, int end);
int		quote_is_data(t_vars *vars, int i);
char	*substr_quote(t_vars *vars, int start, int end);

//cmd_utils
char	**init_cmd_token(void);
t_cmd	*init_cmd(void);
void	free_cmd(t_cmd *cmd);

//quotes_utils
t_quotes	*init_quotes(int start, int end, t_type type);
void		free_quotes(t_quotes *quotes);

//vars_utils
void	init_vars(t_vars *vars, t_shell *shell);
void	c_free_vars(t_vars *vars);
void	free_vars(t_vars *vars);

//args_utils
int	args_loop(t_vars *vars, int *i);
char	**append_args(char **args, char *new);
int	check_empty(t_vars *vars);
int	args_to_word(t_vars *vars, t_cmd *current, int i);
#endif
