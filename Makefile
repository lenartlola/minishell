# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 13:27:39 by hsabir            #+#    #+#              #
#    Updated: 2022/02/20 20:35:47 by hsabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -I ~/.brew/Cellar/readline/8.1.2/include -lreadline -L ~/.brew/Cellar/readline/8.1.2/lib
CFLAGS += -o minishell
#CFLAGS += -g3 -fsanitize=address

LIBFT_DIR = libs/libft/
LFT_NAME = libft.a

NAME = Minishell

FILES = ./srcs/main.c\
	./srcs/ft_env.c\
	./srcs/dollar_utils2.c\
	./srcs/linked_env.c\
	./srcs/pathing.c\
	./srcs/redirection_utils.c\
	./srcs/parse_quotes_args.c\
	./srcs/utils.c\
	./srcs/launch.c\
	./srcs/ft_unset.c\
	./srcs/ft_export.c\
	./srcs/builtin.c\
	./srcs/tokenizing.c\
	./srcs/parsing.c\
	./srcs/prompt.c\
	./srcs/exec_cmds.c\
	./srcs/piping.c\
	./srcs/ascii_init.c\
	./srcs/free.c\
	./srcs/error.c\
	./srcs/str_utils.c\
	./srcs/quotes.c\
	./srcs/quotes_utils.c\
	./srcs/arg_utils.c\
	./srcs/vars_utils.c\
	./srcs/cmd_utils.c\
	./srcs/fd_utils.c\
	./srcs/heredocing.c\
	./srcs/redirection.c\
	./srcs/signal_utils.c\
	./srcs/env_utils.c\
	./srcs/path_utils.c\
	./srcs/dollar_utils.c

all : $(NAME)

$(NAME): $(LFT_NAME)
	$(MAKE) all -sC $(LIBFT_DIR)/
	gcc $(CFLAGS) $(FILES) $(LFT_NAME)

$(LFT_NAME):
	$(MAKE) all -sC $(LIBFT_DIR)/
	cp $(LIBFT_DIR)/$(LFT_NAME) $(LFT_NAME)

fclean:
	rm -f $(NAME)
	rm -f $(LFT_NAME)
	$(MAKE) fclean -sC $(LIBFT_DIR)

clean:
	rm -f $(LFT_NAME)
	$(MAKE) fclean -sC $(LIBFT_DIR)

re: fclean clean all
	$(MAKE) re -sC $(LIBFT_DIR)

.PHONY: clean fclean all re
