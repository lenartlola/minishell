/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:19:12 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/05 17:45:59 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


char	*build_new_tkn(t_vars *vars, t_quotes q_tmp, char *tmp)
{
	char		*a;
	char		*b;
	char		*swap;
	char		*s_end;
	t_quotes	env;

	a = ft_substr(vars->str, 0, q_tmp.start);
	if (!a)
		return (NULL);
	env.start = ft_strlen(a);
	env.end = ft_strlen(a) + ft_strlen(tmp) - 1;
	env.type = ENVS;
	set_quotes_data(vars, vars->env, env);
	b = ft_substr(vars->str, q_tmp.end, ft_strlen(vars->str));
	if (tmp == NULL)
		swap = ft_strdup(a);
	else
		swap = ft_strjoin(a, tmp);
	s_end = ft_strjoin(swap, b);
	free(a);
	free(b);
	free(swap);
	return (s_end);
}

int	get_c_index(char *str, char c)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	sig_child(int sig)
{
	(void)sig;
}

int	last_pid(t_cmd *cmd)
{
	cmd = last_cmd(cmd);
	return (cmd->pid);
}
