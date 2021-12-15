/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:13:59 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/15 17:47:37 by hsabir           ###   ########.fr       */
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

char	*init_prompt(void)
{
	char	*user;
	char	*path;
	char	*prompt;

	user = getenv("USER");
	if (!user)
		exit (EXIT_FAILURE);
	path = get_path(path);
	prompt = ft_calloc(sizeof(char), 1024);
	ft_strlcat(prompt, "[", ft_strlen(prompt) + 2);
	ft_strlcat(prompt, user, ft_strlen(prompt) + ft_strlen(user) + 1);
	ft_strlcat(prompt, "@", ft_strlen(prompt) + 2);
	ft_strlcat(prompt, path, ft_strlen(path) + ft_strlen(path)+ 1);
	ft_strlcat(prompt, "] ~ ", ft_strlen(prompt) + 5);
	free (path);
	return (prompt);
	//printf("%s\n", prompt);
}
