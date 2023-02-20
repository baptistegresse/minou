all:
	gcc sources/main.c sources/lexer.c sources/expand.c sources/parse_cmd.c sources/env.c -lreadline libft/libft.a && ./a.out