/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:35:25 by bgresse           #+#    #+#             */
/*   Updated: 2022/11/25 12:12:10 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static int	is_newline(char *rest, char newline)
{
	size_t	index;

	index = 0;
	if (!rest)
		return (0);
	if (newline == '\0')
		return (0);
	while (rest[index++])
		if (rest[index] == newline)
			return (1);
	return (0);
}

static char	*read_file(char *rest, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	read_bytes = 1;
	while (!is_newline(rest, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		buffer[read_bytes] = '\0';
		rest = rest_join_buffer(rest, buffer);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_file(rest, fd);
	if (!rest)
		return (NULL);
	line = get_before_newline_character(rest);
	rest = get_after_newline_character(rest);
	return (line);
}
