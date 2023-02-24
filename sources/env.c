/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:35 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/24 14:23:32 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_env	*add_node(t_env *head, char *key, char *value)
{
	t_env	*node;

	node = new_node(key, value);
	node->next = head;
	return (node);
}

t_env	*new_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->key = ft_strndup(key, ft_strlen(key));
	node->value = ft_strndup(value, ft_strlen(value));
	return (node);
}

void	ft_parse_env(t_env **head, char **envp)
{
	size_t	i;
	char	*equal;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key = ft_strndup(envp[i], equal - envp[i]);
			value = ft_strdup(equal + 1);
			*head = add_node(*head, key, value);
			free(key);
		}
		i++;
	}
}