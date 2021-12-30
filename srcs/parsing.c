/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 09:57:44 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/30 17:37:16 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_env(char *path, char *cmd)
{
	int	i;
	char	*ret_join;

	i = 0;
	ret_join = ft_strjoin(path, cmd);
	while (path[i])
	{
		if (!(access(ret_join, X_OK)))
		{
			free(ret_join);
			return (1);
		}
		else
			i++;
	}
	free(ret_join);
	return (0);
}

char	*check_cmd(char *cmd, t_shell *shell)
{
	char	*path;
	int		i;
	char	**split;
	char	*full_path;
	char	*full_cmd;
	i = 0;
	path = getenv("PATH");
	split = ft_split(path, ':');
	while (split[i])
	{
		full_path = ft_strjoin(split[i], "/");
		if (check_env(full_path, cmd))
		{
			full_cmd = ft_strjoin(full_path, cmd);
			exec_path_cmd(full_cmd, shell);
			free(split);
			free(full_path);
			free(full_cmd);
			break ;
		}
		free(split[i]);
		free(full_path);
		i++;
	}
	return (NULL);
}
int	builtin(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->cmd->token[i])
	{
		if (!ft_strncmp(shell->cmd->token[i],"env",3))
			return(ft_env(shell));
		else if (!ft_strncmp(shell->cmd->token[i],"echo",4))
			return (ft_echo(shell->cmd->token + i));
		else if (!ft_strncmp(shell->cmd->token[i],"cd",2))
			return (ft_cd(shell->cmd->token + 1, shell));
		else if (!ft_strncmp(shell->cmd->token[i],"export",6))
			return (ft_export(shell->cmd->token, shell));
		i++;
	}
	return (0);
}
void	get_cmd(t_shell *shell)
{
	unsigned int i;
	unsigned int a;

	a = 0;
	i = 0;

	if (!builtin(shell))
		check_cmd(shell->cmd->token[0], shell);
}

int	heredoc(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;

	cmd = shell->cmd;
	i = -1;
	while (shell->cmd)
	{
		if (shell->cmd->redirection)
		{
			while (shell->cmd->redirection[++i])
			{
				if (redirection_type(shell->cmd->redirection[i]) != HEREDOC)
					continue ;
				if (!parse_heredoc(shell->cmd->redirection[i + 1], shell, cmd))
					return (0);
			}
		}
		shell->cmd = shell->cmd->next;
	}
	shell->cmd = cmd;
	return (1);
}

int	launch(t_shell *shell, int *status, char **env)
{
	int	first;
	int	fd[2];

	first = 1;
	while (shell->cmd)
	{
		if (!shell->cmd->next)
		{
			get_cmd(shell);
			*status = -1;
		}
		else
		{
			if (!fd_set_in_out(shell, fd, first))
				return (0);
			exec_pipe_cmd(shell, env, fd[0]);
		}
		shell->cmd = shell->cmd->next;
		first = 0;
	}
	return (1);
}

void	parsing(t_shell *shell, char **env)
{
	int		status;
	t_cmd	*ptr;

	status = 0;
	ptr = shell->cmd;
	if (heredoc(shell))
	{
		if (!launch(shell, &status, env))
			close_fds(ptr);
	}
	free_cmd(ptr);
	shell->cmd = NULL;
	/*while (shell->cmd)
	{
		if (!shell->cmd->next)
		{
			get_cmd(shell);
			status = -1;
		}
		else
		{
			//printf("next -> %s\n", shell->cmd->token[0]);
			get_pipes(shell);
			shell->n_pipes = 1;
			shell->pipe_flag = 1;
			break ;
		}
		shell->cmd = shell->cmd->next;
	}*/
	//if (shell->n_pipes == 1)
	//	printf("Hello pipes\n");
	//if (!builtin(shell))
	//	printf("Error\n");
	/*if (shell->n_pipes)
	{
		if (shell->pipe_flag == 1)
		{
		//	parse_pipes(shell);
		}
	}
	else
	{
		get_cmd(shell);
	}
	return (1);*/
}
