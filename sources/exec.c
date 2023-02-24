/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:03:11 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/24 16:04:17 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Handles the executions of the commands and returns the corresponding error
if the command was not found. */

int	ft_list_size(t_env *head)
{
	int count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**ft_join_envp(t_env **head)
{
	t_env	*current;
	char	**envp;
	size_t	i;

	i = 0;
	current = *head;
	envp = malloc(sizeof(char *) * ft_list_size(*head));
	while (current)
	{
		envp[i++] = ft_strjoin(current->key, ft_strjoin("=", current->value));
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	ft_exec(t_data *data)
{
	int		i;
	char	*cmd;
	char	**envp;

	i = -1;
	envp = ft_join_envp(&data->head_env);
	execve(data->cmds->full_cmd[0], data->cmds->full_cmd, envp);
	if (data->paths)
	{
		while (data->paths[++i])
		{
			cmd = ft_strjoin(data->paths[i], data->cmds->full_cmd[0]);
			if (!cmd)
				return ;
			execve(cmd, data->cmds->full_cmd, envp);
			free(cmd);
		}
	}
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(data->cmds->full_cmd[0], 2);
	ft_putstr_fd("\n", 2);
	return ;
}

/* Handles everything related to children processes. */

void	ft_incubator(t_data *data)
{
	if (close(data->end[0]) == -1)
		return (perror("close pipe"));
	if (data->cmds->infile > 0)
		if (dup2(data->cmds->infile, STDIN_FILENO) == -1)
			return ;
	if (data->cmds->outfile > 1)
		if (dup2(data->cmds->outfile, STDOUT_FILENO) == -1)
			return ;
	if (data->cmds->outfile == 0)
		if (dup2(data->end[1], STDOUT_FILENO) == -1)
			return (perror("dup2 end[1]"));
	ft_exec(data);
	return ;
}

/* Creates a child process for every command and links them together
with pipes */

void	pipex_commands(t_data *data)
{
	while (data->cmds)
	{
		if (pipe(data->end) == -1)
			return ((void)perror("pipe"));
		data->cmds->cmd_pid = fork();
		if (data->cmds->cmd_pid == -1)
			return ((void)perror("Fork"));
		if (data->cmds->cmd_pid != 0 && close(data->end[1]) == -1)
			return ((void)perror("close pipe"));
		if (data->cmds->cmd_pid == 0)
			ft_incubator(data);
		if (dup2(data->end[0], STDIN_FILENO) == -1)
			return ((void)perror("dup2 end[0]"));
		if (close(data->end[0]) == -1)
			return ((void)perror("close pipe"));
		data->cmds = data->cmds->next;
	}
}

/* Runs our commands with pipex_commands, then closes our remaining fds
and waits for children processes to be done */

void	pipex(t_data *data)
{
	int			status;
	t_cmdlist	*head;

	head = data->cmds;
	pipex_commands(data);
	data->cmds = head;
	while (data->cmds)
	{
		if (data->cmds->outfile > 1 && close(data->cmds->outfile) == -1)
			perror("close outfile");
		data->cmds = data->cmds->next;
	}
	data->cmds = head;
	while (data->cmds)
	{
		waitpid(data->cmds->cmd_pid, &status, 0);
		data->cmds = data->cmds->next;
	}
	exit (1);
}
