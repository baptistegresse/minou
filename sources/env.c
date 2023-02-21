/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:35 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/21 16:30:28 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*new_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	return (node);
}

t_env	*add_node(t_env *head, char *key, char *value)
{
	t_env	*node;

	node = new_node(key, value);
	node->next = head;
	return (node);
}

void	ft_parse_env(t_env **head, char **envp)
{
	size_t	i;
	char	*equal;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			*equal = '\0';
			*head = add_node(*head, envp[i], equal + 1);
		}
		i++;
	}
}
