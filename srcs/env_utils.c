/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 20:43:20 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/01 16:08:56 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_arraylen(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value != NULL)
			i++;
		env = env->next;
	}
	return (i);
}

char	**copy_el_to_arr(t_env *src, char **dst)
{
	char	*stock;
	int		i;

	i = 0;
	while (src)
	{
		if (src->value != NULL)
		{
			dst[i] = ft_strjoin(src->name, "=");
			stock = dst[i];
			dst[i] = ft_strjoin(stock, src->value);
			free(stock);
			if (dst[i] == NULL)
			{
				double_free(dst);
				return (NULL);
			}
			i++;
		}
		src = src->next;
	}
	return (dst);
}

char	**get_env_array(t_env *env)
{
	char	**ptr;
	int		len;

	len = ft_arraylen(env);
	ptr = ft_calloc(len + 1, sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	ptr = copy_el_to_arr(env, ptr);
	free_envs(env);
	return (ptr);
}

void	free_envs(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		env->name = NULL;
		if (env->value)
			free(env->value);
		env->value = NULL;
		free(env);
		env = NULL;
		env = tmp;
	}
}

t_env	*last_env(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

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
