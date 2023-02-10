/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:37:18 by bgresse           #+#    #+#             */
/*   Updated: 2022/11/25 12:11:49 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 666
# endif

char	*get_next_line(int fd);

char	*rest_join_buffer(char *rest, char *buffer);

char	*get_before_newline_character(char *rest);
char	*get_after_newline_character(char *rest);

#endif