/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:53 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/21 16:20:33 by bgresse          ###   ########.fr       */
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
            return (ft_strjoin(ft_strjoin(""GREEN"➜  "CYAN"", temp->value),
				""PURPLE"@minishell >"RESET""));
        temp = temp->next;
    }
    return (""GREEN"➜  "CYAN"guest"PURPLE"@minishell >"RESET"");
}
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*buffer = NULL;
	char	*prompt;

	data = malloc(sizeof(t_data));
	ft_parse_env(&data->head, envp);
	prompt = get_env(&data->head, "USER");
	while (1) 
	{
		buffer = readline(prompt);
		if (!buffer)
			break;
		add_history(buffer);
		if (ft_strstr(buffer, "cd"))
			ft_built_in_cd(buffer);
		if (ft_strstr(buffer, "exit"))
			ft_built_in_exit();
		if (ft_strstr(buffer, "pwd"))
			ft_built_in_pwd();
		if (ft_strstr(buffer, "env"))
			ft_built_in_env(&data->head);
		if (ft_strstr(buffer, "export"))
			ft_built_in_export(&data->head, buffer);
		if (ft_strstr(buffer, "unset"))
			ft_built_in_unset(&data->head, buffer);
		ft_parse_cmd(data, buffer);
	}
	printf("exit");
	return (0);	
}
