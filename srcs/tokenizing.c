/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 22:55:45 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2022/01/07 17:11:50 by hsabir           ###   ########.fr       */
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

/*
 * The base of the program here we decide how to handle what
 * the users write. It could be monkey typing so we have to be careful
 * whar we are reciving and how tto manage them.
 * ----------------------------------------------------------------
 * The first approach was to handle the pipes at first
 * but we soon realised that we should have took care of quotes :)
 * ----------------------------------------------------------------
 * Check if any type 'single', or "double" exist, if yes,
 * so find out its indexes of start and end, and as well its type.
 * ----------------------------------------------------------------
 * Once found quotes and its details then look for dollar sign
 * and handle it carefully as bash does.
 * ----------------------------------------------------------------
 */

int	tokenizing(t_shell *shell)
{
	t_vars	vars;
	int		len;

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
}
