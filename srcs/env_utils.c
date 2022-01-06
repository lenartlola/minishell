/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 20:43:20 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/06 12:31:08 by lgyger           ###   ########.fr       */
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

int	check_path_env(t_env **env, char *name)
{
	t_env	*ptr;

	if (env)
	{
		ptr = *env;
		while (*env)
		{
			if (ft_strcmp((*env)->name, name) == 0)
				return (1);
			*env = (*env)->next;
		}
		*env = ptr;
	}
	return (0);
}
