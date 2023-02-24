/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:24:08 by bgresse           #+#    #+#             */
/*   Updated: 2023/02/24 15:20:15 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_built_in_cd(char *string)
{
	char	**paths;

	paths = ft_split_tokens(string, " ");
	if (chdir(paths[1]) == -1)
		perror("chdir()");
}
