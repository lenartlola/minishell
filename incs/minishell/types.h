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

enum e_tok_type {
	CHAR_GEN	= -1,
	CHAR_PIPE	= '|',
	CHAR_AMP	= '&',
	CHAR_QOUTE	= '\'',
	CHAR_DQOUTE	= '\"',
	CHAR_SC		= ';',
	CHAR_WS		= ' ',
	CHAR_ESCSEQ	= '\\',
	CHAR_TAB	= '\t',
	CHAR_NL		= '\n',
	CHAR_GT		= '>',
	CHAR_LS		= '<',
	CHAR_DL		= '$',
	CHAR_NULL	= '\0',
	CHAR_QUEST	= '?',
	CHAR_OPR	= '(',
	CHAR_CPR	= ')',
	CHAR_OCL	= '{',
	CHAR_CCL	= '}',
	TOK			= -1
};

struct	s_tkn {
	char	*data;
	int		type;
	t_tkn	*next;
}

struct	s_lexer {
	t_tkn	*tkn_list;
	int		n_tokens;
}

/* Asterik */
typedef struct s_ast	t_ast;

struct s_ast {
	int		type;
	char	*data;
	t_ast	*left;
	t_ast	*right;
};

#endif /* end of include guard TYPES_H */

