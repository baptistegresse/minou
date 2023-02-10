#include "../includes/minishell.h"

/*
	The new_node function allocates memory for a new
	node and initializes it with a given key and value.
*/

static t_env *new_node(char *key, char *value)
{
	t_env *node;

	node = (t_env*)malloc(sizeof(t_env));
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return node;
}

/*
	The add_node function adds a new node to the 
	head of the head list using new_node.
*/

static t_env *add_node(t_env *head, char *key, char *value)
{
	t_env *node;

	node = new_node(key, value);
	node->next = head;
	return node;
}

/*
	The ft_parse_env function iterates through an envp environment 
	array and adds each key-value entry to the linked list using add_node.
*/

void	ft_parse_env(t_env **head, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
    	char *equal = ft_strchr(envp[i], '=');
    	if (equal)
    	{
      		*equal = '\0';
      		*head = add_node(*head, envp[i], equal + 1);
    	}
    i++;
    }
}
