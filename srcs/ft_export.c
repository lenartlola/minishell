/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 09:46:58 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/05 15:07:54 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../incs/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

/*char	**sort(char **ev,int n_array)
{
	int i;
	int j;
	char *temp;
	
	i = 0;
	while (i < n_array)
	{
		j = 0;
    		while(j < n_array-1-i)
		{
      			if(ft_strcmp(ev[j], ev[j+1]) > 0)
			{
				temp = ft_strdup(ev[j]);
        			ev[j] = ft_strdup(ev[j+1]);
        			ev[j+1] = ft_strdup(temp);
			}
			j++;
		}
		i++;
	}
	return (ev);
}
*/void	ft_sort(t_env *env, int lenenv)
{
	int	j;
	char *temp;
	char *ntemp;

	j = 0;
	while (j < lenenv)
	{
		if (ft_strcmp(env->name,env->next->name) > 0)
		{
			ntemp = ft_strdup(env->value);
			temp = ft_strdup(env->name);
			env->name = ft_strdup(env->next->name);
			env->value = ft_strdup(env->next->value);
			env->next->name = ft_strdup(temp);
			env->next->value = ntemp;
		}
		env = env->next;
		j++;
	}
}

t_env	*sort(t_env *env, int lenenv)
{
	int	i;

	i = 0;
	while (i < lenenv)
	{
		ft_sort(env, lenenv - 1 - i);
		i++;
	}
	return (env);
}

int	ft_export(char **cmd, t_shell *shell, t_env **tenv)
{
	unsigned int i;
	t_env *tmp;
	char **ret;

	i = 0;
	tmp = g_env;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (cmd[1] == NULL)
	{
		tmp = g_env;
		tmp = sort(tmp, i);
		while(tmp)
		{
			printf("declare -x %s=\"%s\"\n",tmp->name,tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		ret = ft_split(cmd[1], '=');
		tmp = new_env(ret[0],ret[1]);
		env_add_back(&shell->env,tmp);
	}
	g_env = shell->env;
	return (1);
}
