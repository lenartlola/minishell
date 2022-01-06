/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:06:39 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/06 12:09:50 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_putstring(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	close_heredoc_fds(t_cmd *ptr)
{
	t_cmd	*cmd;

	cmd = ptr;
	while (cmd)
	{
		if (cmd->in != 0)
			close_error(cmd->in);
		cmd = cmd->next;
	}
}

int	wait_process(t_shell *shell, int pid, int *fd, t_cmd *ptr)
{
	int	status;

	waitpid(pid, &status, 0);
	close_error(fd[1]);
	if (shell->cmd->in != 0)
		close_error(shell->cmd->in);
	shell->cmd->in = fd[0];
	if (WIFSIGNALED(status))
	{
		close_heredoc_fds(ptr);
		ft_putchar_fd('\n', 2);
		shell->ret = 1;
		return (0);
	}
	shell->ret = WEXITSTATUS(status);
	return (1);
}

void	child_heredoc(int *fd, char *delim)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close_error(fd[0]);
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(delim, line, ft_strlen(delim)) == 0)
			break ;
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close_error(fd[1]);
	exit(EXIT_SUCCESS);
}

int	parse_heredoc(char *delim, t_shell *shell, t_cmd *ptr)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		perror("Heredoc pipe\n");
		close_heredoc_fds(ptr);
		return (0);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_heredoc(fd, delim);
	if (pid == -1)
		perror("Fork error\n");
	return (wait_process(shell, pid, fd, ptr));
}
