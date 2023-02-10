#ifndef MINISHELL_H
#define MINISHELL_H

#define SPACE 32
#define SQUOTE 39
#define DQUOTE 34

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_data
{
	t_env	*head_env;
}					t_data;

void	ft_parse_env(t_env **head, char **envp);
char	**ft_lexer(char const *s, char c);
char	**ft_expand(t_env **head, char	**cmds);
char	**ft_cmds_split(char **cmds);

#endif