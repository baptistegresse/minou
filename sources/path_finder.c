/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:34:37 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/23 18:11:51 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_pathfinder(char **envp)
{
	char	*paths_line;
	char	**paths;
	int		i;

	i = 0;
	if (!envp[0] || !envp)
		return (0);
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (0);
	paths_line = envp[i] + 5;
	paths = ft_split_slash(paths_line, ':');
	return (paths);
}
