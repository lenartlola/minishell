/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:59:03 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/03 15:44:30 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	is_builtin(char *arg)
{
	t_builtin_cmd	cmd;

	cmd = N_B_IN;
	if (arg == NULL)
		return (0);
	if (ft_strcmp("echo", arg) == 0)
		cmd = ECHO_M;
	else if (ft_strcmp("pwd", arg) == 0)
		cmd = PWD_M;
	else if (ft_strcmp("cd", arg) == 0)
		cmd = CD_M;
	else if (ft_strcmp("export", arg) == 0)
		cmd = EXPORT_M;
	else if (ft_strcmp("unset", arg) == 0)
		cmd = UNSET_M;
	else if (ft_strcmp("env", arg) == 0)
		cmd = ENV_M;
	return (cmd);
}

/*void	main_redirection(t_shell *shell)
{
	if (!*shell->cmd->redirection)
	{
		shell->std_in = dup(0);
		if (shell->std_in == -1)
			free_all(shell, 1, "Std_in dup in main redirection\n");
		shell->std_out = dup(1);
		if (shell->std_out == -1)
			free_all(shell, 1, "Std_out dup in main redirection\n");
		redirection_handler(shell);
	}
}
*/
int	launch_builtin(int tmp, t_shell *shell, int in_fork)
{
//	if (in_fork)
//		main_redirection(shell);
	if (tmp == ECHO_M)
		shell->ret = ft_echo(shell->cmd->token);
	else if (tmp == ENV_M)
		shell->ret = ft_env(shell);
	else if (tmp == CD_M)
		shell->ret = ft_cd(shell->cmd->token + 1, shell);
	else if (tmp == EXPORT_M)
		shell->ret = ft_export(shell->cmd->token, shell);
	else if (tmp == UNSET_M)
		shell->ret = ft_unset(shell->cmd->token,shell);
	if (!in_fork)
		swap_fds(shell->std_in, shell->std_out);
	shell->std_in = 0;
	shell->std_out = 1;
	return (1);
}

int	ft_cd(char **cmd, t_shell *shell)
{

	if (cmd[0] == NULL)
		cmd[0] = getenv("HOME");
	getcwd(shell->ev[31],100);
//	shell->ev[31] = ft_strjoin("OLDPWD=",shell->ev[31]);
	if (chdir(cmd[0]) != 0)
	{
		printf("cd: no such file or directory: %s\n",cmd[0]);
		return (0);
	}
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
				printf("%c",str[i + 1]);
			u = 1;
		}
		if (str[i] != '\\' && u != 1)
			printf("%c",str[i]);
		i++;
	}
}

int	ft_echo(char **cmd)
{
	int	i;
	
	i = 1;
	while(cmd[i])
	{
		if(i == 1 && (!ft_strncmp(cmd[1], "-n",ft_strlen(cmd[1]))))
			i++;
//		printf("%s\n",cmd[i]);
		ft_printecho(cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if ((ft_strncmp(cmd[1],"-n",ft_strlen(cmd[1]))))
		printf("\n");
	return (1);
}

int	ft_env(t_shell *shell)
{
	t_env *tmp;

	tmp = shell->env;
	while (tmp)
	{
		printf("%s=%s\n",tmp->name,tmp->value);
		tmp = tmp->next;
	}
	//oldpwd = (g_env[a] + 4);
	return (1);
}
