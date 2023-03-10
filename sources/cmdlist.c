/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:06:44 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/24 16:16:23 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Creates a new node in our linked list of commands.*/

void	ft_newnode(t_cmdlist **cmds);

void    ft_print_env(t_env **head)
{
    t_env   *current;

    current = *head;
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

/* Handles redirections for each command and 
creates a new command node everytime a '|' is found.
-5 means the redirection will go in a pipe. */

void    ft_redirection(char **parsed_line, t_cmdlist *cmds)
{
    int         i;

    i = -1;
    while(parsed_line[++i])
    {
        if (*parsed_line[i] == '|')
		{
            ft_newnode(&cmds);
			if (cmds->outfile == 1)
				cmds->outfile = 0;
			cmds = cmds->next;
		}
		else if (*parsed_line[i] == '<')
		{
			cmds->infile = open(parsed_line[i + 1], O_RDONLY);
			if (cmds->infile == -1)
				perror("open infile");
		}
		else if (*parsed_line[i] == '>')
		{
			cmds->outfile = open(parsed_line[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmds->outfile == -1)
				perror("open outfile");
		}
    }
}

/* For each node of our cmd list,
stores the command in a char ** that we can send directly to execve*/

void	ft_fullcmds(char **parsed_line, t_cmdlist *cmds)
{
	int			i;
	int			j;

	cmds->full_cmd = malloc(sizeof(char *) * 50);
	i = -1;
	j = 0;
	while(parsed_line[++i])
	{
		if (*parsed_line[i] == '|')
		{
			cmds->full_cmd[j] = 0;
			cmds = cmds->next;
			cmds->full_cmd = malloc(sizeof(char *) * 50);
			j = 0;
		}
		else if ((*parsed_line[i] == '>' || *parsed_line[i] == '<'))
			i++;
		else
			cmds->full_cmd[j++] = parsed_line[i];
	}
}

t_cmdlist	*ft_cmdlist(t_data *data, char *cmd_line)
{
	char		**parsed_line;
	t_cmdlist	*cmds;
	
	cmds = 0;
	ft_newnode(&cmds);
	parsed_line = ft_split_tokens(cmd_line, "<|>");
	parsed_line = ft_expand_path(&data->head_env, parsed_line);
	//parsed_line = ft_expand_var(&data->head_env, parsed_line);
	ft_redirection(parsed_line, cmds);
	ft_fullcmds(parsed_line, cmds);
	ft_print_cmdlist(cmds);
	return (cmds);
}
