# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 13:27:39 by hsabir            #+#    #+#              #
#    Updated: 2022/01/04 19:59:38 by 1mthe0wl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CFLAGS = -I ~/.brew/Cellar/readline/8.1.1/include -lreadline -L ~/.brew/Cellar/readline/8.1.1/lib -o minishell
LIBFT_DIR = libs/libft/
NAME = Minishell
FILES = ./srcs/main.c\
       ./srcs/arg_utils.c\
	./srcs/builtin.c\
	./srcs/cmd_utils.c\
	./srcs/dollar_utils.c\
	./srcs/env_utils.c\
	./srcs/error.c\
	./srcs/exec_cmds.c\
	./srcs/fd_utils.c\
	./srcs/free.c\
	./srcs/ft_export.c\
	./srcs/ft_unset.c\
	./srcs/heredocing.c\
	./srcs/parsing.c\
	./srcs/ascii_init.c\
	./srcs/path_utils.c\
	./srcs/piping.c\
	./srcs/prompt.c\
	./srcs/quotes_utils.c\
	./srcs/redirection.c\
	./srcs/quotes.c\
	./srcs/signal_utils.c\
	./srcs/str_utils.c\
	./srcs/tokenizing.c\
	./libs/libft/libft.a\
	./incs/minishell.h\
	./srcs/vars_utils.c

all : $(NAME)

$(NAME):
	cd libs/libft/ && $(MAKE)
	gcc $(CFLAGS) $(FILES)

fclean:
	rm -f $(NAME)
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
re: fclean clean all
	$(MAKE) -C $(LIBFT_DIR) re
.PHONY: clean fclean all re
