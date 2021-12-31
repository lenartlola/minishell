/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 20:43:20 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/31 20:49:36 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_env	*get_env_list(char	**env)
{
	t_env	*new_env;
	size_t	len;
	int		i;

	i = -1;
	env = NULL;
	while (env[++i])
	{
		len = ft_strchr(env[i], '=') - env[i];
		if (ft_strncmp("OLDPWD", env[i], 7) == 0)
		{
			env_add_back()
		}
	}
}
