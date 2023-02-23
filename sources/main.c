/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:18:53 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/23 18:10:53 by bgresse          ###   ########.fr       */
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
	data->paths = ft_pathfinder(&data->head_env);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
}

void    ft_prompt(t_data *data)
{
    char    	*buffer;
    int         status;
    int         pid;
	char		*prompt;

	
	//prompt = get_prompt(data->head_env, "USER");
    while (1) 
    {
        buffer = readline("salut >");
        if (!buffer)
            break ;
		add_history(buffer);
        data->cmds = ft_cmdlist(buffer);
        pid = fork();
        if (pid == 0)
            pipex(data);
        waitpid(pid, &status, 0);
    }
    printf("Ciao, Bye !");
}

int    main(int argc, char **argv, char **envp)
{
    t_data data;
	
	//ft_parse_env(&data.head_env, envp);
    data_init(argc, argv, envp, &data);
    ft_prompt(&data);
    return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	*data;
// 	char	*buffer = NULL;
// 	char	*prompt;

// 	data = malloc(sizeof(t_data));

// 	while (1) 
// 	{
// 		buffer = readline(prompt);
// 		if (!buffer)
// 			break;
// 		add_history(buffer);
// 		if (ft_strstr(buffer, "cd"))
// 			ft_built_in_cd(buffer);
// 		if (ft_strstr(buffer, "exit"))
// 			ft_built_in_exit();
// 		if (ft_strstr(buffer, "pwd"))
// 			ft_built_in_pwd();
// 		if (ft_strstr(buffer, "env"))
// 			ft_built_in_env(&data->head_env);
// 		if (ft_strstr(buffer, "export"))
// 			ft_built_in_export(&data->head_env, buffer);
// 		if (ft_strstr(buffer, "unset"))
// 			ft_built_in_unset(&data->head_env, buffer);
// 		ft_parse_cmd(data, buffer);
// 	}
// 	printf("exit");
// 	return (0);	
// }