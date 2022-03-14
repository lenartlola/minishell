///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   parsing.c                                          :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2021/12/15 09:57:44 by 1mthe0wl          #+#    #+#             */
///*   Updated: 2022/01/05 17:25:33 by lgyger           ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "../incs/minishell.h"
//
//int	check_env(char *path, char *cmd)
//{
//	int			i;
//	char		*ret_join;
//
//	i = 0;
//	ret_join = ft_strjoin(path, cmd);
//	while (path[i])
//	{
//		if (!(access(ret_join, X_OK)))
//		{
//			free(ret_join);
//			return (1);
//		}
//		else
//			i++;
//	}
//	free(ret_join);
//	return (0);
//}
//
//char	*check_cmd(char *cmd, t_shell *shell)
//{
//	int		i;
//	char	**split;
//	char	*full_path;
//	char	*full_cmd;
//
//	i = 0;
//	split = ft_split(getenv("PATH"), ':');
//	while (split[i])
//	{
//		full_path = ft_strjoin(split[i], "/");
//		if (check_env(full_path, cmd))
//		{
//			full_cmd = ft_strjoin(full_path, cmd);
//			free(split);
//			free(full_path);
//			return (full_cmd);
//		}
//		free(split[i]);
//		free(full_path);
//		i++;
//	}
//	return (NULL);
//}
//
//int	heredoc(t_shell *shell)
//{
//	t_cmd	*cmd;
//	int		i;
//
//	cmd = shell->cmd;
//	while (shell->cmd)
//	{
//		i = -1;
//		if (shell->cmd->redirection)
//		{
//			while (shell->cmd->redirection[++i])
//			{
//				if (redirection_type(shell->cmd->redirection[i]) != HEREDOC)
//					continue ;
//				if (!parse_heredoc(shell->cmd->redirection[i + 1], shell, cmd))
//					return (0);
//			}
//		}
//		shell->cmd = shell->cmd->next;
//	}
//	shell->cmd = cmd;
//	return (1);
//}
//
//int	launch(t_shell *shell, int *status, char **env)
//{
//	int	f;
//	int	fd[2];
//
//	f = 1;
//	while (shell->cmd)
//	{
//		if (f && !shell->cmd->redirection[0] && is_builtin(*shell->cmd->token))
//		{
//			exec_built_in(shell, 1);
//			*status = -1;
//		}
//		else
//		{
//			if (!fd_set_in_out(shell, fd, f))
//				return (0);
//			exec_pipe_cmd(shell, env, fd[0]);
//		}
//		if (shell->cmd->next)
//			close_error(fd[1]);
//		if (shell->cmd->in != 0)
//			close_error(shell->cmd->in);
//		shell->cmd = shell->cmd->next;
//		f = 0;
//	}
//	return (1);
//}
//
//void	parsing(t_shell *shell, char **env)
//{
//	int		status;
//	t_cmd	*ptr;
//
//	status = 0;
//	shell->error = 0;
//	ptr = shell->cmd;
//	if (heredoc(shell))
//	{
//		if (!launch(shell, &status, env))
//			close_fds(ptr);
//		if (status != -1 && !shell->error)
//			wait_all_process(ptr, shell);
//	}
//	free_cmd(ptr);
//	shell->cmd = NULL;
//}
