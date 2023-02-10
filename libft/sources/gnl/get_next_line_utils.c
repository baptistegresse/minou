/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:35:35 by bgresse           #+#    #+#             */
/*   Updated: 2022/11/25 13:25:45 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static size_t	ft_strlenc(char *string)
{
	size_t	index;

	index = 0;
	if (!string)
		return (0);
	while (string[index])
		index++;
	return (index);
}

char	*get_after_newline_character(char *rest)
{
	char	*after_line;
	size_t	index_rest;
	size_t	index_line;

	index_rest = 0;
	while (rest[index_rest] && rest[index_rest] != '\n')
		index_rest++;
	if (rest[index_rest] == '\0')
		return (free(rest), rest = NULL, NULL);
	if (rest[index_rest] == '\n')
		index_rest++;
	after_line = malloc(sizeof(char) * (ft_strlenc(rest) - index_rest + 1));
	if (!after_line)
		return (free(rest), rest = NULL, NULL);
	index_line = 0;
	while (rest[index_rest])
		after_line[index_line++] = rest[index_rest++];
	after_line[index_line] = 0;
	return (free(rest), rest = NULL, after_line);
}

char	*get_before_newline_character(char *rest)
{
	char	*line;
	size_t	index;

	index = 0;
	if (!rest[index])
		return (NULL);
	while (rest[index] && rest[index] != '\n')
		index++;
	line = malloc(sizeof(char) * (index + 2));
	if (!line)
		return (NULL);
	index = 0;
	while (rest[index] && rest[index] != '\n')
	{
		line[index] = rest[index];
		index++;
	}
	if (rest[index] == '\n')
		line[index++] = '\n';
	line[index] = '\0';
	return (line);
}

char	*rest_join_buffer(char *rest, char *buffer)
{
	char	*result;
	size_t	index_result;
	size_t	index_copy;

	if (!rest)
	{
		rest = malloc(sizeof(char) * (1));
		if (!rest)
			return (free(rest), NULL);
		rest[0] = 0;
	}
	if (!rest || !buffer)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlenc(rest) + ft_strlenc(buffer) + 1));
	if (!result)
		return (NULL);
	index_result = 0;
	index_copy = 0;
	while (rest[index_copy])
		result[index_result++] = rest[index_copy++];
	index_copy = 0;
	while (buffer[index_copy])
		result[index_result++] = buffer[index_copy++];
	result[index_result] = 0;
	return (free(rest), result);
}
