/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:41:20 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/16 20:36:45 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	child_process(int *fd, char **cmd, char *env)
{
	close(fd[READ_END]);
	if (dup2(fd[WRITE_END], STDOUT_FILENO) < 0)
		printf("Error:");
	close(fd[WRITE_END]);
	if (execve(cmd[0], cmd, &env) < 0)
	{
		printf("minishell: %s command execution failed\n", cmd[0]);
		exit (EXIT_FAILURE);
	}
}

void	parent_process(int *fd, char **cmd, char *env)
{
	int	pid;

	close(fd[WRITE_END]);
	pid = fork();
	if (!pid)
	{
		if (dup2(fd[READ_END], STDIN_FILENO) < 0)
		{	
			printf("Error: duplicating filedescriptor 0\n");
			exit (EXIT_FAILURE);
		}
		printf("path test: %s\n", cmd[0]);
		if (execve(cmd[0], cmd, &env) < 0)
		{
			printf("Minishell: %s executing command failed\n", cmd[0]);
			exit (EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		close(fd[READ_END]);
	else
	{
		printf("Minishell: error in parrent process\n");
		exit (EXIT_FAILURE);
	}
}

void	exec_pipe_cmd(char *path, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int	status;

	if (pipe(fd) < 0)
	{
		printf("pipe err\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (!pid)
		child_process(fd, shell->cmds_pipe[0], path);
	else if (pid > 0)
		parent_process(fd, shell->cmds_pipe[1], path);
	else
	{
		printf("Error in forking pipes\n");
		exit (EXIT_FAILURE);
	}
	wait(&status);
	wait(&status);
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
		printf("path: %s\n", path);
		execv(path, shell->tokens);
	}
	else if (pid > 0)
		child_pid = waitpid(pid, &status, 0);
}
