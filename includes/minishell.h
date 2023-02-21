#ifndef MINISHELL_H
#define MINISHELL_H

#define SPACE 32
#define SQUOTE 39
#define DQUOTE 34
#define DOLLAR 36
#define TILDE 126
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_data
{
	t_env	*head;
}					t_data;


// parsing
void	ft_parse_env(t_env **head, char **envp);
char	**ft_expand_var(t_env **head, char	**cmds);
char	**ft_expand_path(t_env **head, char **cmds);
void    ft_parse_cmd(t_data *data, char *buffer);
char	**ft_lexer(char const *string, char c);
char    *ft_get_env(t_env **head, char *key);

// builtin
void	ft_built_in_env(t_env **head);
void	ft_built_in_unset(t_env **head, char *key);
void	ft_built_in_export(t_env **head, char *string);
void	ft_built_in_cd(char *string);
void    ft_built_in_exit(void);
void	ft_built_in_pwd(void);
void    ft_built_in_chat(void);
t_env 	*add_node(t_env *head, char *key, char *value);
t_env	*new_node(char *key, char *value);

#endif