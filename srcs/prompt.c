/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:13:59 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2022/03/13 15:10:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_path(char *path)
{
	int		size;
	char	*ptr;

	size = 1024;
	path = (char *)malloc((size_t)size);
	if (path)
		ptr = getcwd(path, (size_t)size);
	else
		exit (EXIT_FAILURE);
	return (ptr);
}

void	init_prompt()
{
	char	*user;
	char	*path = NULL;

	user = getenv("USER");
	if (!user)
		exit (EXIT_FAILURE);
	path = get_path(path);
	g_shell.prompt = ft_calloc(sizeof(char), 1024);
	ft_strlcat(g_shell.prompt, "[", ft_strlen(g_shell.prompt) + 2);
	ft_strlcat(g_shell.prompt, user,
		ft_strlen(g_shell.prompt) + ft_strlen(user) + 1);
	ft_strlcat(g_shell.prompt, "@", ft_strlen(g_shell.prompt) + 2);
	ft_strlcat(g_shell.prompt, path,
		ft_strlen(g_shell.prompt) + ft_strlen(path)+ 1);
	ft_strlcat(g_shell.prompt, "] ~ ", ft_strlen(g_shell.prompt) + 5);
	free (path);
}
