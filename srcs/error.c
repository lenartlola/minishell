/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:03:26 by hsabir            #+#    #+#             */
/*   Updated: 2022/03/14 09:10:45 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	print_error(char *str)
{
	if (str == NULL)
		perror("minishell: unexpected error\n");
	else
		perror(str);
	exit(EXIT_FAILURE);
}

int	print_error_ret(const char *str, int ret)
{
	if (str == NULL)
		perror("minishell: unexpected error\n");
	else
		perror(str);
	return (ret);
}

void	close_error(int fd)
{
	if (close(fd) == -1)
		perror("Close\n");
}

void	close_fds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->in != 0)
			close_error(cmd->in);
		if (cmd->out != 1)
			close_error(cmd->out);
		cmd = cmd->next;
	}
}

void	wcard_err(t_tkn *const *tkn, t_tkn *head)
{
	ft_putstr_fd((*tkn)->data, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	tok_del(head);
}
