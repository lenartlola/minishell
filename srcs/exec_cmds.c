/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:41:20 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2022/01/06 12:25:07 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	exec_pipe_cmd(t_shell *shell, char **env, int fd_in)
{
	char	**ptr;
	int		status;

	child_handler(shell);
	shell->cmd->pid = fork();
	if (shell->cmd->pid == 0)
	{
		close_unused_fd(shell, fd_in);
		redirection_handler(shell);
		swap_fds(shell->cmd->in, shell->cmd->out);
		if (shell->error)
			exit(EXIT_FAILURE);
		if (exec_built_in(shell, 1))
			exit(shell->ret);
		shell->cmd->path = check_cmd(*shell->cmd->token, shell);
		if (!shell->cmd->path)
		{
			printf("minish: %s: command not found\n", *shell->cmd->token);
			free_cmd(shell->cmd);
			exit (EXIT_FAILURE);
		}
		ptr = get_env_array(shell->env);
		execve(shell->cmd->path, shell->cmd->token, ptr);
		perror(*shell->cmd->token);
	}
	else if (shell->cmd->pid == -1)
		perror("pipe execution fork\n");
	else if (shell->cmd->pid > 0)
		waitpid(shell->cmd->pid, &status, WCONTINUED);
	shell->lreturn = WEXITSTATUS(status);
	return (0);
}

int	exec_built_in(t_shell *shell, int in_fork)
{
	int	tmp;

	if (*shell->cmd->token)
	{
		tmp = is_builtin(*shell->cmd->token);
		if (tmp != N_B_IN)
			return (launch_builtin(tmp, shell, in_fork));
	}
	return (0);
}

void	exec_path_cmd(char *path, t_shell *shell)
{
	int		status;
	pid_t	pid;
	pid_t	child_pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		execv(path, shell->cmd->token);
	}
	else if (pid > 0)
		child_pid = waitpid(pid, &status, 0);
}
