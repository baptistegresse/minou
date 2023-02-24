/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:53 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/24 15:43:12 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

static char    *get_prompt(t_env *head, char *key)
{
    t_env	*temp;

    temp = head;
    while (temp)
    {
        if (ft_strcmp(temp->key, key) == 0)
            return (ft_strjoin(ft_strjoin(""GREEN"➜  "CYAN"", temp->value),
				""PURPLE"@minishell >"RESET""));
        temp = temp->next;
    }
    return (""GREEN"➜  "CYAN"guest"PURPLE"@minishell >"RESET"");
}

void	data_init(int argc, char **argv, char **envp, t_data *data)
{
	data->envp = envp;
	data->argv = argv;
	data->argc = argc;
    ft_parse_env(&data->head_env, envp);
	data->paths = ft_pathfinder(&data->head_env);
}

void    ft_prompt(t_data *data)
{
    char    	*buffer;
    int         status;
    int         pid;
    char        *prompt;

    prompt = get_prompt(data->head_env, "USER");
    while (42) 
    {
        buffer = readline(prompt);
        if (!buffer)
            break ;
		add_history(buffer);
        data->cmds = ft_cmdlist(data, buffer);
        pid = fork();
        if (pid == 0)
            pipex(data);
        waitpid(pid, &status, 0);
    }
    printf("exit\n");
}

int    main(int argc, char **argv, char **envp)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data_init(argc, argv, envp, data);
    ft_prompt(data);
    return (0);
}
