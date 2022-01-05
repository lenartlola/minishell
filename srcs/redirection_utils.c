/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:48:00 by lgyger            #+#    #+#             */
/*   Updated: 2022/01/05 17:52:04 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	redirection_type(char *redirection)
{
	int	mode;

	mode = -1;
	redirection_in(redirection, &mode);
	redirection_out(redirection, &mode);
	return (mode);
}

void	dup_and_close(int fd_in, int fd_out)
{
	if (dup2(fd_in, fd_out) == -1)
		perror("Dup2Close\n");
	close_error(fd_in);
}

void	redirection_in(char *redirection, int *mode)
{
	if (*redirection == '<')
	{
		if (*(redirection + 1) == '<')
			*mode = HEREDOC;
		else
			*mode = REDIRECT_IN;
	}
}

void	redirection_out(char *redirection, int *type)
{
	if (*redirection == '>')
	{
		if (*(redirection + 1) == '>')
			*type = REDIRECT_D_OUT;
		else
			*type = REDIRECT_OUT;
	}
}
