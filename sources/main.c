/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:53 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/20 20:38:02 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*buffer = NULL;
	char	*prompt;


	data = malloc(sizeof(t_data));
	prompt = malloc(100);
	ft_parse_env(&data->head, envp);

	prompt = get_env(&data->head, "USER");
	while (1) 
	{
		buffer = readline(prompt);
		if (!buffer)
			break;
		add_history(buffer);
		if (ft_strstr(buffer, "chat"))
			ft_builtin_chat();
		if (ft_strstr(buffer, "env"))
			ft_builtin_env(&data->head);
		if (ft_strstr(buffer, "unset"))
			ft_builtin_unset(&data->head, buffer);
		ft_parse_cmd(data, buffer);
	}
	printf("exit");
	return (0);	
}
