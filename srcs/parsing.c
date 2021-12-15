/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 1mthe0wl </var/spool/mail/evil>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 09:57:44 by 1mthe0wl          #+#    #+#             */
/*   Updated: 2021/12/15 17:38:17 by lgyger           ###   ########.fr       */
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
			return (1);
		else
			i++;
	}
	free(ret_join);
	return (0);
}
void	test(char *path,t_shell *shell)
{
	int status;
	status = 0;
	pid_t pid;
	pid_t chpid;
	printf("%s\n",shell->tokens[1]);
	pid = fork();
	if (pid == 0)
	{
		execv(path,shell->tokens);

	}
	else if (pid > 0)
		chpid = waitpid(pid,&status,0);
}
char	*check_cmd(char *cmd, t_shell *shell)
{
	char	*path;
	int		i;
	char	**split;
	char	*full_path;
	i = 0;
	path = getenv("PATH");
	printf("cmd: %s\n", cmd);
	split = ft_split(path, ':');
	while (split[i])
	{
		//printf("split: %s\n", split[i]);
		full_path = ft_strjoin(split[i], "/");
		//printf("split: %s\n", ret_cmd);
		if (check_env(full_path, cmd))
		{
//			printf("OK\n");
//			if (ft_strncmp(cmd,"ls",2) == 0)
				test(ft_strjoin(full_path,cmd),shell);
			break ;
		}
		else
		{
//			printf("KO\n");
		}
		i++;
	}
}
void	get_cmd(t_shell *shell)
{
	unsigned int i;
	unsigned int a;

	a = 0;
	i = 0;
	while (shell->cmdline[i])
	{
		if (shell->cmdline[i] == '&' || shell->cmdline[i] == '|')
		{
			shell->cmds = ft_substr(shell->cmdline,a,i);
//			printf("%s\n",shell->cmds);
			a = i + 2;
			shell->tokens = ft_split(shell->cmds, ' ');
			check_cmd(shell->tokens[0], shell);
			i += 2;
		}
		else
			i++;
	}
	shell->cmds = ft_substr(shell->cmdline,a,i);
	check_cmd(shell->tokens[0], shell);
//	printf("%s\n",shell->cmds);
}
void	parsing(t_shell *shell)
{
	unsigned int i;

	i = 0;
	if (shell->n_pipes)
		printf("Pipes\n");
	else
	{
		get_cmd(shell);
		while (shell->tokens[i])
		{
//			check_cmd(shell->tokens[i], shell);
			i++;
		}
	}
}
