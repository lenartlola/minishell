/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 20:43:20 by hsabir            #+#    #+#             */
/*   Updated: 2022/03/13 14:52:00 by                  ###   ########.fr       */
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

// re:bonus

char	*ft_getenv(const char *path)
{
	int		path_size;
	char	*aux;
	char	*ret;
	t_list	*tmp;

	tmp = *g_shell.env;
	aux = ft_strjoin(path, "=");
	path_size = ft_strlen(aux);
	while (tmp)
	{
		if (ft_strncmp(aux, (char *)tmp->content, path_size) == 0)
		{
			ret = ft_substr((char *)tmp->content, path_size,
							ft_strlen((char *)tmp->content) - path_size);
			free(aux);
			return (ret);
		}
		tmp = tmp->next;
	}
	free(aux);
	return (NULL);
}

static int	protect_shlvl(t_list *gaux, char **tmp, int *aux)
{
	char	*tmp2;

	if ((*aux) < 0)
	{
		(*aux) = 1;
		free((*tmp));
		(*tmp) = ft_itoa((*aux));
		tmp2 = ft_strjoin("SHLVL=", (*tmp));
		free(gaux->content);
		gaux->content = ft_strdup(tmp2);
		return (1);
	}
	return (0);
}

static void	increment_shlvl(t_list *gaux, char *tmp, int aux)
{
	char	*tmp2;

	aux++;
	free(tmp);
	tmp = ft_itoa(aux);
	tmp2 = ft_strjoin("SHLVL=", tmp);
	free(gaux->content);
	gaux->content = ft_strdup(tmp2);
	free(tmp2);
	free(tmp);
}

static void	update_shlvl(void)
{
	t_list	*gaux;
	char	*tmp;
	int		aux;

	gaux = *g_shell.env;
	while (gaux)
	{
		if (ft_strncmp("SHLVL=", (char *)gaux->content, 6) == 0)
			break ;
		gaux = gaux->next;
	}
	if (!gaux)
	{
		ft_lstadd_back(g_shell.env, ft_lstnew(ft_strdup("SHLVL=1")));
		return ;
	}
	tmp = ft_substr((char *)gaux->content, 6,
			ft_strlen((char *)gaux->content) - 6);
	aux = ft_atoi(tmp);
	if (protect_shlvl(gaux, &tmp, &aux) == 1)
		return ;
	else
		increment_shlvl(gaux, tmp, aux);
}

static char	*set_vars(char *pwd, const char *sh_lvl, char *aux)
{
	if (getcwd(pwd, PATH_MAX))
	{
		aux = ft_strjoin("PWD=", pwd);
		ft_lstadd_back(g_shell.env, ft_lstnew((void *)ft_strdup(aux)));
	}
	ft_lstadd_back(g_shell.env, ft_lstnew(ft_strdup((void *)sh_lvl)));
	return (aux);
}

void	fill_env(char **env)
{
	int		i;
	char	*pwd;
	char	*sh_lvl;
	char	*aux;

	i = -1;
	g_shell.env = (t_list **)ft_calloc(1, (sizeof(t_list *)));
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd || !g_shell.env)
		return ;
	aux = NULL;
	sh_lvl = ft_strdup("SHLVL=1");
	if (env[0])
	{
		while (env[++i])
			ft_lstadd_back(g_shell.env, ft_lstnew((void *) ft_strdup(env[i])));
		update_shlvl();
	}
	else
		aux = set_vars(pwd, sh_lvl, aux);
	if (aux)
		free(aux);
	free(pwd);
	free(sh_lvl);
}
