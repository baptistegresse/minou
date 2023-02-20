/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:09 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/21 00:29:00 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_expand_path(t_env **head, char **cmds)
{
    size_t i;

    i = 0;
    while(cmds[i])
    {
        if (cmds[i][0] == TILDE && !cmds[i][1])
        {
            cmds[i] = ft_get_env(head, "HOME");
            break;
        }
        else if (cmds[i][0] == TILDE && cmds[i][1] == '/')
        {
            cmds[i] = ft_strjoin(ft_get_env(head, "HOME"), cmds[i] + 1);
            break;
        }
        i++;
    }
    return (cmds);
}

static char *ft_check_key(t_env **head_env, char *key)
{
    t_env *temp;

    temp = *head_env;
    while (temp)
    {
        if (ft_strcmp(temp->key, key) == 0)
            return (temp->value);
        temp = temp->next;
    }
    return ("");
}

static char *ft_expand_string(t_env **head, char *string)
{
    size_t i;
    size_t start;
    char *new_string;

    if (string[0] == SQUOTE)
        return (string);
    new_string = ft_strdup("");
    i = 0;
    start = 0;
    while (string[i] && string[i] != DOLLAR)
        i++;
    new_string = ft_strjoin(new_string, ft_substr(string, start, i - start));
    start = i;
    while (string[start + 1] && ft_isalnum(string[start + 1]))
        start++;
    new_string = ft_strjoin(new_string, ft_check_key(head, ft_substr(string, i + 1, start - i)));
    new_string = ft_strjoin(new_string, ft_substr(string, start + 1, ft_strlen(string) - start - 1));
    free(string);
    return (new_string);
}

char    *ft_remove_quotes(char *string)
{
    size_t  i;
    
    i = 0;
    while (string[i])
    {
        if (string[i] == SQUOTE)
        {
            ft_strcpy(string + i, string + i + 1);
            while (string[i] && string[i] != SQUOTE)
                i++;
            ft_strcpy(string + i, string + i + 1);
        }
        if (string[i] == DQUOTE)
        {
            ft_strcpy(string + i, string + i + 1);
            while (string[i] && string[i] != DQUOTE)
                i++;
            ft_strcpy(string + i, string + i + 1);
        }
        i++;
    }
    return (string);
}

char **ft_expand_var(t_env **head, char **cmds)
{
    char    *old_cmd;
    size_t  i;

    i = 0;
    while (cmds[i])
    {
        if (cmds[i][0] == SQUOTE)
            break ;
        while (ft_strchr(cmds[i], DOLLAR))
        {
            old_cmd = cmds[i];
            cmds[i] = ft_expand_string(head, cmds[i]);
        }
        i++;
    }
    i = 0;
    while (cmds[i])
    {
        cmds[i] = ft_remove_quotes(cmds[i]);
        i++;
    }
    return (cmds);
}