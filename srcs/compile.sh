gcc -g3 -fsanitize=address main.c tokenizing.c parsing.c prompt.c exec_cmds.c piping.c ../libs/libft/libft.a -lreadline -o minishell && ./minishell
