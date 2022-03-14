/**
 * @author      : hypn0x (hypn0x@$HOSTNAME)
 * @file        : types
 * @created     : Sunday Mar 13, 2022 05:09:35 UTC
 */

#ifndef TYPES_H

#define TYPES_H

/* Lexer analyser */
typedef struct s_tkn	t_tkn;
typedef struct s_lexer	t_lexer;
typedef struct s_ast	t_ast;
typedef struct s_bltin	t_bltin;
typedef struct s_shell	t_shell;
typedef int	t_bool;

/* Environments */
typedef struct s_env	t_env;

struct s_env {
	char	*name;
	char	*value;
	t_env	*next;
};


/* Lexer analyzer */

struct	s_tkn {
	char	*data;
	int		type;
	t_tkn	*next;
};

struct	s_lexer {
	t_tkn	*tkn_list;
	int		n_tokens;
};

// lex additional support
typedef struct s_lexadd {
	t_tkn	*tkn;
	char	c;
	int		type;
	int		st;
	int		i;
	int		j;
}	t_lexadd;

// token additional support
typedef struct s_tknadd {
	int		cnt;
	int		semaphore;
	int		is_heredoc;
	t_tkn	*prev;
	t_tkn	*aux;
}	t_tknadd;

// wildcard additional support
typedef struct s_wcadd {
	const char	*stgt;
	const char	*swc;
	const char	*tgt_end;
	int			ret;
	int			st;
}	t_wcadd;

/* AST */

struct s_ast {
	int		type;
	char	*data;
	t_ast	*left;
	t_ast	*right;
};

/* Expand */

typedef struct s_expand {
	int		start;
	int		end;
	int		curly;
	char	*name;
	char	*value;
}	t_expand;

/* Built-in */

struct s_bltin {
	char	*name;
	int		(*f)(char **);
	t_bltin	*next;
};

/* Shell */

/*
 * lstatus:	last return status.
 * cmdline:	the line given by prompt.
 */

struct s_shell
{
	int			lstatus;
	char		*cmdline;
	t_tkn		*prev;
	t_tkn		*tkn;
	t_ast		**current_ast;
	t_ast		cmd_ast;
	t_bltin		*builtin;
	t_bool		is_expd;
	t_bool		tokdel;
	t_list		**env;
	//t_cmd		*cmd;
	char		**tokens;
	int			ret;
	int			std_in;
	int			std_out;
	int			error;
	int			pipe_cmd_exist;
	int			lreturn;
	char			*cmds;
	char			*prompt;
	char			**ev;
	char			**exp;
	//struct termios	term;
};

extern t_shell	g_shell;

#endif /* end of include guard TYPES_H */
