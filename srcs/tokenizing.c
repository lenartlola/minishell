/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 22:55:45 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/17 12:24:53 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_trim(char *str)
{
	char *ret;

	ret = ft_strtrim(str, " ");
	free(str);
	return (ret);
}

int pipe_counter(char *str, char c)
{
	unsigned int ret;
	size_t i;
	
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			ret++;
		i++;
	}
	return (ret);
}

void	tokenizing(t_shell *shell)
{
	int		i;
	int		check_len;

	i = 0;
	check_len = 0;
	shell->n_pipes = pipe_counter(shell->cmdline, '|');
	if (shell->n_pipes)
	{
		shell->tokens = ft_split(shell->cmdline, '|');
		while (shell->cmdline[check_len])
			check_len++;
		if (check_len <= shell->n_pipes)
			printf("minishell: syntax error near unexpected token `%s'\n", shell->cmdline);
		while (i <= shell->n_pipes && shell->n_pipes < check_len)
		{
			shell->tokens[i] = ft_trim(shell->tokens[i]);
			shell->cmds_pipe[i] = ft_split(shell->tokens[i], ' ');
			check_len++;
			i++;
		}
	}
	else
	{
		shell->tokens = ft_split(shell->cmdline, ' ');
		/*while (shell->cmds[i])
		{
			printf("cmds: %s\n", shell->cmds[i]);
			i++;	
		}*/
	}
}
