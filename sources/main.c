#include "../includes/minishell.h"
#include <string.h>

static char    *get_env(t_env **head, char *key)
{
    t_env	*temp;

    temp = *head;
    while (temp)
    {
        if (ft_strcmp(temp->key, key) == 0)
            return (ft_strjoin(temp->value, "@ouimishell ?> "));
        temp = temp->next;
    }
    return ("guest@ouimishell ?> ");
}

void remove_env_node(t_env **head, char *key) {

    t_env *current = *head, *prev = NULL;

    if (current != NULL && strcmp(current->key, key) == 0)
	{
        *head = current->next;
        free(current->key);
        free(current->value);
        free(current);
        return;
    }
    while (current != NULL && strcmp(current->key, key) != 0)
	{
        prev = current;
        current = current->next;
    }
    if (current == NULL) 
        return;
    prev->next = current->next;
    return (free(current->key), free(current->value), free(current));
}

void	ft_builtin_unset(t_env **head, char *key)
{
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key + 6) == 0)
			remove_env_node(head, key + 6);
		temp = temp->next;
	}
}

void	ft_builtin_env(t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*buffer = NULL;
	char	*prompt;

	data = malloc(sizeof(t_data));
	prompt = malloc(100);
	ft_parse_env(&data->head_env, envp);

	prompt = get_env(&data->head_env, "USER");
	while (1) 
	{
		buffer = readline(prompt);
		if (!buffer)
			break;
		if (ft_strcmp(buffer, "env\n"))
			ft_builtin_env(&data->head_env);
		if (ft_strstr(buffer, "unset"))
			ft_builtin_unset(&data->head_env, buffer);
		ft_parse_cmd(data, buffer);
	}
	printf("exit");
	return (0);	
}
