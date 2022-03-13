/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 22:55:45 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2022/03/13 05:39:33 by hypn0x           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_trim(char *str)
{
	char	*ret;

	ret = ft_strtrim(str, " ");
	free(str);
	return (ret);
}

/*
 * Check if a pipe exist before or after the quotes,
 * skip the spaces if found,
 */

int	parse_loop(t_vars *vars, int len)
{
	t_cmd	*tmp;
	int		i;
	int		ret;

	tmp = vars->cmd;
	i = 0;
	while (i < len)
	{
		i += trim_spaces(&vars->str[i]);
		ret = parse_quotes_args(vars, &i, tmp);
		if (ret == -1)
			return (-1);
		else if (ret != 0)
			continue ;
		if (parse_pipes(vars, &i, &tmp, len) == -1)
			return (-1);
	}
	return (0);
}

int	tokenizing(t_shell *shell, t_lexer *lex)
{
	size_t	len;

	len = ft_strlen(shell->cmdline);
/*
	shell->cmd = init_cmd();
	if (!shell->cmd)
	{
		free_envs(shell->env);
		perror("Close");
	}
	vars.lreturn = shell->lreturn;
	init_vars(&vars, shell);
	len = ft_strlen(vars.str);
	parse_quotes(&vars, len);
	parse_dollar(&vars, len);
	len = ft_strlen(vars.str);
	if (parse_loop(&vars, len) == -1)
	{
		c_free_vars(&vars);
		shell->cmd = NULL;
		return (-1);
	}
	free(vars.str);
	free_quotes(vars.quotes);
	free_quotes(vars.env);
	return (0);
	*/
}

static int	check_line(char *line)
{
	char	*aux;

	if (line == NULL || *line == '\0' || *line == '\n' || is_comment(line))
	{
		free_line(line, is_alloc);
		return (1);
	}
	aux = line;
	while (*aux != '\0')
	{
		if (ft_isblank(*aux) == 0)
			break ;
		aux++;
	}
	if (*aux == '\0')
	{
		free_line(line, is_alloc);
		return (1);
	}
	return (0);
}

int	handle_line(t_shell *shell)
{
	t_lexer	lex;
	t_ast	*ast;
	int		ret;

	ast = NULL;
	if (check_line(shell->cmdline) == 1)
		return (-1);
	ret = tokenizing(shell, &lex);
}

