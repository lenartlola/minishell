/**
 * @author      : hypn0x (wubbalubba@dubdub)
 * @file        : types_enum
 * @created     : Sunday Mar 13, 2022 10:48:08 CET
 */

#ifndef TYPES_ENUM_H

#define TYPES_ENUM_H

/* Lexer analyzer */

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

// States
enum {
	ST_IN_QUOTE = 0,
	ST_IN_DQUOTE,
	ST_IN_ESC,
	ST_IN_CURLY,
	ST_GENERAL
};


#endif /* end of include guard TYPES_ENUM_H */
