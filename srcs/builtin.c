/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:10:25 by lgyger            #+#    #+#             */
/*   Updated: 2021/12/21 16:15:06 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

void	src(t_shell *shell, char *oldpwd)
{
	char	*str;
	t_list	*mem;

	mem = shell->ev;
	while (mem)
	{
		str = mem->content;
		if (!ft_strncmp(str, "PWD=", 4))
		{
			str = ft_strjoin("PWD=", getcwd(NULL, 1000));
			mem->content = str;
		}
		else if (!ft_strncmp(str, "OLDPWD", 6))
		{
			str = ft_strjoin("OLDPWD=", oldpwd);
			mem->content = str;
		}
		mem = mem->next;
	}
}

int	ft_cd(char **cmd, t_shell *shell)
{
	char	mem[1000];

	getcwd(mem, 1000);
	if (cmd[0] == NULL)
		cmd[0] = getenv("HOME");
	if (chdir(cmd[0]) != 0)
	{
		printf("cd: no such file or directory: %s\n", cmd[0]);
		return (0);
	}
	src(shell, mem);
	init_prompt(shell);
	return (1);
}

void	ft_printecho(char *str)
{
	int	i;
	int	u;

	u = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (u == 0)
				printf("%c", str[i + 1]);
			u = 1;
		}
		if (str[i] != '\\' && u != 1)
			printf("%c", str[i]);
		i++;
	}
}

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (i == 1 && (!ft_strncmp(cmd[1], "-n", 2)))
			i++;
		ft_printecho(cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if ((ft_strncmp(cmd[1], "-n", 2)))
		printf("\n");
	return (1);
}

int	ft_env(t_shell *shell)
{
	char	*str;
	char	test[8];
	t_list	*cp;

	cp = shell->ev;
	while (cp)
	{
		str = cp->content;
		if (!ft_strncmp(str, "OLDPWD", 7))
		{
			if (!ft_strncmp(str, "OLDPWD=", 8))
				printf("%s\n", str);
		}
		else
			printf("%s\n", str);
		cp = cp->next;
	}
	return (1);
}
