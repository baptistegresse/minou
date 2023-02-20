#include "../includes/minishell.h"

char    *ft_get_env(t_env **head_env, char *key)
{
    t_env	*temp;

    temp = *head_env;
    while (temp)
    {
        if (ft_strcmp(temp->key, key) == 0)
            return (temp->value);
        temp = temp->next;
    }
    return (NULL);
}

void    ft_parse_cmd(t_data *data, char *buffer)
{
    char	**cmds;

    cmds = ft_lexer(buffer, ' ');
    cmds = ft_expand_path(&data->head_env, cmds);
    cmds = ft_expand_var(&data->head_env, cmds);

    for(int i = 0; cmds[i] != NULL; i++)
        printf("%s:", cmds[i]);
    printf("\n");
}