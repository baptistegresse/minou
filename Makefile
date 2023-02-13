all:
	gcc sources/main.c sources/lexer.c sources/expand.c sources/cmds_split.c sources/env.c -lreadline libft/libft.a && ./a.out