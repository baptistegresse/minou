#include "../includes/minishell.h"

char	**ft_expand_path(t_env **head, char **cmds)
{
    int i;

    i = 0;
    while(cmds[i])
    {
        if (cmds[i][0] == '~' && !cmds[i][1])
        {
            cmds[i] = ft_get_env(head, "HOME");
            break;
        }
        else if (cmds[i][0] == '~' && cmds[i][1] == '/')
        {
            cmds[i] = ft_strjoin(ft_get_env(head, "HOME"), cmds[i] + 1);
            break;
        }
        i++;
    }
    return (cmds);
}

char    *ft_check_key(t_env **head, char *key)
{
    t_env	*temp;

    temp = *head;
    while (temp)
    {
        if (ft_strcmp(temp->key, key) == 0)
            return (temp->value);
        temp = temp->next;
    }
    return ("");
}

char	*ft_expand_string(t_env **head, char *string)
{
    
}

char    **ft_expand_var(t_env **head, char **cmds)
{
    int i;

    i = 0;
    while (cmds[i])
    {
        if (ft_strchr(cmds[i], '$'))
            cmds[i] = ft_expand_string(head, cmds[i]);
        i++;
    }
    return (cmds);
}
