/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:34:37 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/24 00:32:21 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_pathfinder(t_env **head)
{
	char	*paths_line;
	char	**paths;

	paths_line = ft_get_env(head, "PATH");
	paths = ft_split_slash(paths_line, ':');
	return (paths);
}
