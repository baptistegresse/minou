/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:58 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/24 00:30:02 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_env(t_env **head_env, char *key)
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

char 	**ft_parse_cmd(t_data *data, char *buffer)
{
	char	**cmds;

	cmds = ft_lexer(buffer, ' ');
	cmds = ft_expand_path(&data->head_env, cmds);
	cmds = ft_expand_var(&data->head_env, cmds);
	return (cmds);
}
