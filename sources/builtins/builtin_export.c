#include "../../includes/minishell.h"


void    ft_builtin_export(t_env **head, char *string)
{
    t_env   *temp;

    temp = *head;
    while (temp)
    {
        if (ft_strcmp(temp->key, key) == 0)
        {
            free(temp->value);
            temp->value = ft_strdup(value);
            return ;
        }
        temp = temp->next;
    }
    ft_env_add_back(head, ft_env_new(key, value));
}