/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:35:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/03/13 17:45:23 by                  ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

// Intern includes
# include "minishell/main.h"
# include "../libs/libft/incs/libft.h"
# include "minishell/types.h"
# include "minishell/defs.h"
# include "minishell/types_enum.h"
//# include <minishell/colors.h>
//# include <minishell/utils.h>
//# include <minishell/signals.h>
//# include <minishell/prompt.h>
//# include <minishell/lexer.h>
//# include <minishell/parser.h>
//# include <minishell/ast.h>
//# include <minishell/exec.h>
//# include <minishell/read_config.h>

// STANDARD LIBS
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <dirent.h>
# include <unistd.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>

// READLINE
# include <readline/readline.h>
# include <readline/history.h>

# ifndef PATH_MAX
#  define PATH_MAX 256
# endif

typedef struct s_quotes	t_quotes;
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

//extern t_env	*g_env;

typedef enum s_red_type
{
	HEREDOC,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_D_OUT,
}	t_red_type;

typedef enum s_type
{
	SIMPLE,
	DOUBLE,
	NONE,
	ENVS
}	t_type;

typedef struct s_quotes
{
	int		start;
	int		end;
	t_type		type;
	t_quotes	*next;
}	t_quotes;

typedef struct s_vars
{
	t_cmd		*cmd;
	t_quotes	*quotes;
	t_quotes	*env;
	t_env		*env_vars;
	char		*str;
	int		*last_ret;
	int		lreturn;
}	t_vars;

typedef struct s_cmd
{
	char	**token;
	char	**redirection;
	char	*path;
	int	pid;
	int	in;
	int	out;
	t_cmd	*next;
}	t_cmd;

char		*build_new_tkn(t_vars *vars, t_quotes q_tmp, char *tmp);
void		parse_dollar(t_vars *vars, int len);
int			launch_builtin(int tmp, t_shell *shell, int in_fork);
int			check_path_env(t_env **env, char *name);
int			get_path_exec(t_shell *shell);
int			ft_strhas(char *str, char *set);
int			is_xok(char *path);
char		**split_tab(t_env *env);
int			absolute_path(t_shell *shell);
int			add_slash(char **path);
t_env		*get_envs(char	**m_env);
t_env		*last_env(t_env *env);
char		**get_env_array(t_env *env);
t_type		get_type(t_quotes *quotes, int i);
void		free_envs(t_env *env);
int			quotes_error(void);
void		quote_error_exit(t_vars *vars);
void		parrent_handler(void);
t_cmd		*last_cmd(t_cmd *cmd);
t_env		*new_env(char *name, char *value);
void		wait_all_process(t_cmd *cmd, t_shell *shell);

void		child_handler(t_shell *shell);
t_env		*last_env(t_env *env);
int			exec_built_in(t_shell *shell, int in_fork);
char		*check_cmd(char *cmd, t_shell *shell);
void		free_all(t_shell *shell, int exit_p, char *str);
void		swap_fds(int in, int out);
void		dup_and_close(int fd_in, int fd_out);
int			is_builtin(char *arg);
void		redirection_handler(t_shell *shell);
void		close_unused_fd(t_shell *shell, int fd);
int			ft_strcmp(char *s1, char *s2);
void		close_error(int fd);
void		env_add_back(t_env **lst, t_env *new);
void		close_fds(t_cmd *cmd);
int			fd_set_in_out(t_shell *shell, int *fd, int first);
int			parse_heredoc(char *delim, t_shell *shell, t_cmd *ptr);
int			redirection_type(char *redirection);
int			redirection(t_vars *vars, t_cmd *current, int i);
int			tokenizing(const char *line, size_t len, t_lexer *lex);
int			pipe_counter(char *str, char c);
void		blocksig(int sig, void *ptr);
//parsing
int			parse_quotes_args(t_vars *vars, int *i, t_cmd *tmp);
int			parse_pipes(t_vars *vars, int *i, t_cmd **tmp, int len);
void		parsing(t_shell *shell, char **env);
int			fork_pipes(int n, char ***argv, char **env, t_shell *shell);
int			get_c_index(char *str, char c);
char		*build_new_tkn(t_vars *vars, t_quotes q_tmp, char *tmp);
//int	fork_pipes(int n, char *argv, char **env);
//prompt
void		init_prompt();

//exec
void		exec_path_cmd(char *path, t_shell *shell);
int			exec_pipe_cmd(t_shell *shell, char **env, int fd_in);

//piping
int			get_pipes(t_shell *shell);
int			pipe_handler(t_vars *vars, int i, int len, t_cmd **tmp);
int			redirection_type(char *redirection);
void		dup_and_close(int fd_in, int fd_out);
void		redirection_in(char *redirection, int *mode);
void		redirection_out(char *redirection, int *type);
//builtin
int			ft_env(char **null);
int			ft_echo(char **cmd);
int			ft_cd(char **cmd);
int			ft_export(char **cmd);
int			ft_pwd(char **null);
int			ft_unset(char **cmd);
//Init ascii
void		init_ascii(void);
//Free
void		free_struct();
int			double_free(char **array);
//Error
void		print_error(char *str);
void		update_quotes_data(t_quotes *quotes, int size, int i);
void		last_dollar_ret(t_vars *vars, int *i);
void		ignore_dollar(t_vars *vars, int *i);
char		*get_env_value(t_vars *vars, char *name);
int			join_splt(char **out, char **split, int *i);
//Launch
int			is_builtin(char *arg);
int			launch_builtin(int tmp, t_shell *shell, int in_fork);

//quotes/
int			parse_simple_quote(t_vars *vars, t_cmd *current, int i);
int			parse_double_quote(t_vars *vars, t_cmd *current, int i);
int			ft_strhas(char *str, char *set);
void		set_quotes_data(t_vars *vars, t_quotes *quotes, t_quotes tmp);
void		parse_quotes(t_vars *vars, int len);
int			quotes_error(void);

//str_utils
int			get_c_index(char *str, char c);
int			trim_spaces(char *str);
int			is_sep(char c);
int			quote_counter(t_vars *vars, int start, int end);
int			quote_is_data(t_vars *vars, int i);
char		*substr_quote(t_vars *vars, int start, int end);

//cmd_utils
char		**init_cmd_token(void);
t_cmd		*init_cmd(void);
void		free_cmd(t_cmd *cmd);

//quotes_utils
t_quotes	*init_quotes(int start, int end, t_type type);
void		free_quotes(t_quotes *quotes);

//vars_utils
void		c_free_vars(t_vars *vars);
void		free_vars(t_vars *vars);

//args_utils
int			args_loop(t_vars *vars, int *i);
char		**append_args(char **args, char *new);
int			check_empty(t_vars *vars);
int			args_to_word(t_vars *vars, t_cmd *current, int i);
//sig_utils
int			last_pid(t_cmd *cmd);
void		sig_child(int sig);

// re:bonus
/* Lexer */
int			handle_line();
// quotes
void		trim_quotes(char *dst, char *src);
// Expand
int			expand(t_tkn *tkn, int *start, int st);
void		lexer_del(t_lexer *lex);
void		insert_tknlst(t_tkn **tkn, t_tkn **prev, t_lexer *lex, t_tkn *head);
int			handle_expand(t_tkn **tkn, t_tkn **prev, t_lexer *lex, t_tknadd *ts);
// token utils
int			process_tokens(t_lexer *lex);
int			tok_init(t_tkn *tkn, size_t len);
int			init_la(t_lexadd *la, t_lexer *lex, const size_t len);
void		del_node(t_tkn **tkn, t_tkn *prev);
void		tok_del(t_tkn *tkn);
void		rejoin_tknens(t_tkn **tkn, t_tkn **prev, t_lexer *lex, t_tkn *head);


// Inits
void		init_shell(void);

// Environments
void		fill_env(char **env);
char		*ft_getenv(const char *path);

// Errors
int			print_error_ret(const char *str, int ret);
void		print_error(char *str);

// Filters
int			get_ctype(char c);

// general states
int			handle_general_state(t_lexadd *la, const char *line, const size_t len);
// other states
void		handle_other_st(t_lexadd *la);

// Wildcards
int			wc_check(t_tkn *tkn);
int			wc_match(const char *wildcard, const char *target);
void		read_dir(t_tkn **head, DIR *ls, struct dirent *list);
int			handle_wildcards(t_tkn **tkn, t_tkn **prev, t_lexer *lex);
void		wcard_err(t_tkn *const *tkn, t_tkn *head);


#endif 
