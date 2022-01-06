/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:26:01 by lgyger            #+#    #+#             */
/*   Updated: 2022/01/06 12:32:35 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		ptr = last_env(*lst);
		ptr->next = new;
	}
}

t_env	*new_env(char	*name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}

t_env	*last_env(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

t_env	*get_envs(char	**m_env)
{
	t_env	*env;
	size_t	len;
	int		i;

	i = -1;
	env = NULL;
	while (m_env[++i])
	{
		len = ft_strchr(m_env[i], '=') - m_env[i];
		if (ft_strncmp("OLDPWD", m_env[i], 7) == 0)
			env_add_back(&env, new_env(ft_substr(m_env[i], 0, len), NULL));
		else
			env_add_back(&env, new_env(ft_substr(m_env[i], 0, len),
					ft_strdup(m_env[i] + len + 1)));
	}
	return (env);
}
