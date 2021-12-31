/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:57:56 by hsabir            #+#    #+#             */
/*   Updated: 2021/12/31 13:39:45 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	args_r_handler(t_vars *vars, int *i)
{
	if (is_sep(vars->str[*i]))
	{
		ft_printf("minish: syntax error near unexpected token `%c'\n", vars->str[*i]);
		return (-1);
	}
	else if (vars->str[*i] == '\0')
	{
		printf("minish: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	return (1);
}

int	redirection_loop(t_vars *vars, int *i)
{
	int	len;

	len = ft_strlen(vars->str);
	if (args_r_handler(vars, i) == -1)
		return (-1);
	while (*i < len)
	{
		if (is_sep(vars->str[*i]))
			break ;
		else if (ft_strncmp(&vars->str[*i], "\'", 1) == 0)
			*i += get_c_index((&vars->str[*i] + 1), '\'') + 1;
		else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0)
			*i += get_c_index((&vars->str[*i] + 1), '\"') + 1;
		*i += 1;
	}
	return (0);
}

int	redirection(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	int		k;
	char	*tmp;

	j = i + 1;
	if (vars->str[j] == vars->str[j - 1])
		j++;
	tmp = ft_substr(vars->str, i, j - i);
	if (!tmp)
		free_vars(vars);
	current->redirection = append_args(current->redirection, tmp);
	if (!current->redirection)
		free_vars(vars);
	j += trim_spaces(&vars->str[j]);
	k = j;
	if (redirection_loop(vars, &k) == -1)
		return (-1);
	tmp = substr_quote(vars, j, k - 1);
	if (!tmp)
		free_vars(vars);
	current->redirection = append_args(current->redirection, tmp);
	if (!current->redirection)
		free_vars(vars);
	return (k - j);
}

/* ########################################################### */

void	redirection_out(char *redirection, int *type)
{
	if (*redirection == '>')
	{
		if (*(redirection + 1) == '>')
			*type = REDIRECT_D_OUT;
		else
			*type = REDIRECT_OUT;
	}
}

void	redirection_in(char *redirection, int *mode)
{
	if (*redirection == '<')
	{
		if (*(redirection + 1) == '<')
			*mode = HEREDOC;
		else
			*mode = REDIRECT_IN;
	}
}

int	redirection_type(char *redirection)
{
	int	mode;

	mode = -1;
	redirection_in(redirection, &mode);
	redirection_out(redirection, &mode);
	return (mode);
}

/* ############################################################## */

void	dup_and_close(int fd_in, int fd_out)
{
	if (dup2(fd_in, fd_out) == -1)
		perror("Dup2Close\n");
	close_error(fd_in);
}

int	apply_redirection(t_shell *shell, char *filename, int mode)
{
	int	f_fd;

	f_fd = -1;
	if (mode == REDIRECT_IN)
		f_fd = open(filename, O_RDONLY);
	else if (mode == REDIRECT_OUT)
		f_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (mode == REDIRECT_D_OUT)
		f_fd = open(filename, O_CREAT | O_RDWR, O_APPEND, 0644);
	if (f_fd == -1)
	{
		perror(filename);
		return (EXIT_FAILURE);
	}
	if (mode == REDIRECT_OUT || mode == REDIRECT_D_OUT)
		dup_and_close(f_fd, shell->cmd->out);
	else
		dup_and_close(f_fd, shell->cmd->in);
	return (0);
}

void	redirection_handler(t_shell *shell)
{
	int	red;
	int	i;

	i = -1;
	while (shell->cmd->redirection[++i])
	{
		if (redirection_type(shell->cmd->redirection[i]) == -1
			|| redirection_type(shell->cmd->redirection[i]) == HEREDOC)
			continue ;
		red = redirection_type(shell->cmd->redirection[i]);
		i++;
		if (apply_redirection(shell, shell->cmd->redirection[i], red) == 1)
				break ;
	}
	double_free(shell->cmd->redirection);
	shell->cmd->redirection = NULL;
}
