/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:39:21 by lgyger            #+#    #+#             */
/*   Updated: 2022/01/05 17:40:21 by lgyger           ###   ########.fr       */
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

int	launch_builtin(int tmp, t_shell *shell, int in_fork)
{
	if (tmp == ECHO_M)
		shell->ret = ft_echo(shell->cmd->token);
	else if (tmp == ENV_M)
		shell->ret = ft_env(shell);
	else if (tmp == CD_M)
		shell->ret = ft_cd(shell->cmd->token + 1, shell);
	else if (tmp == EXPORT_M)
		shell->ret = ft_export(shell->cmd->token, shell, &shell->env);
	else if (tmp == UNSET_M)
		shell->ret = ft_unset(shell->cmd->token,shell);
	else if (tmp == PWD_M)
		shell->ret = ft_pwd();
	if (!in_fork)
		swap_fds(shell->std_in, shell->std_out);
	shell->std_in = 0;
	shell->std_out = 1;
	return (1);
}
