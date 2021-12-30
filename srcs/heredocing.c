/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:06:39 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/30 17:33:57 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1b;
	unsigned char	*s2b;

	i = 0;
	s1b = (unsigned char *)s1;
	s2b = (unsigned char *)s2;
	if (!s1 || !s2)
		return (-1);
	while (s1b[i] || s2b[i])
	{
		if (s1b[i] != s2b[i])
			return (s1b[i] - s2b[i]);
		i++;
	}
	return (0);
}*/

void	ft_putstring(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
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
	if (wait(&status))
	{
		close_heredoc_fds(ptr);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	return (1);
}

void	child_heredoc(int *fd, char *delim)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close_error(fd[0]);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(delim, line) == 0)
			break ;
		ft_putstring(line, fd[1]);
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
