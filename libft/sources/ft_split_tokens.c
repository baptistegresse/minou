/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:37:03 by zrebhi            #+#    #+#             */
/*   Updated: 2023/02/23 16:20:20 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		ft_quotes(char const *s, int *j);
int			ft_separator(char c, char *charset);
char		**ft_free_strs(char **strs);

static int	ft_words(char const *s, char *charset)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && ft_separator(s[i], " "))
			i++;
		ft_quotes(s, &i);
		while (ft_separator(s[i], charset))
		{
			words++;
			i++;
		}
		if (!ft_separator(s[i], " ") && s[i])
		{
			words++;
			i++;
		}
		while (s[i] && !ft_separator(s[i], charset) && \
			!ft_separator(s[i], " \"\'"))
			i++;
	}
	return (words);
}

static char	*ft_dupstr(char const *s, int i, int j)
{
	char	*dup;
	int		x;

	dup = malloc(sizeof(char) * (j - i + 1));
	if (!dup)
		return (0);
	x = 0;
	while (s[i] && i < j)
		dup[x++] = s[i++];
	dup[x] = 0;
	return (dup);
}

typedef struct s_split
{
	int		i;
	int		j;
	int		x;
	char	**strs;
}			t_split;

static void	ft_lines2(char const *s, char *charset, t_split *lines)
{
	while (s[lines->j] && !ft_separator(s[lines->j], charset) && \
		!ft_separator(s[lines->j], " "))
	{
		lines->j++;
		ft_quotes(s, &lines->j);
	}
	if (ft_separator(s[lines->j], charset) || \
	ft_separator(s[lines->j], " ") || (!s[lines->j] && \
	!ft_separator(s[lines->j - 1], " ")))
	{
		lines->strs[lines->x] = ft_dupstr(s, lines->i, lines->j);
		if (lines->strs[lines->x] == 0)
			return ((void)ft_free_strs(lines->strs));
		lines->x++;
		lines->i = lines->j;
	}
}

static char	**ft_lines(char const *s, char *charset, t_split *lines)
{
	while (s[lines->i])
	{
		while (s[lines->i] && ft_separator(s[lines->i], " "))
			lines->i++;
		while (ft_separator(s[lines->i], charset))
		{
			lines->strs[lines->x] = ft_dupstr(s, lines->i, lines->i + 1);
			if (lines->strs[lines->x] == 0)
				return (ft_free_strs(lines->strs));
			lines->i++;
			lines->x++;
		}
		while (s[lines->i] && ft_separator(s[lines->i], " "))
			lines->i++;
		lines->j = lines->i;
		ft_quotes(s, &lines->j);
		ft_lines2(s, charset, lines);
	}
	return (lines->strs);
}

char	**ft_split_tokens(char const *s, char *charset)
{
	t_split	lines;

	lines.i = 0;
	lines.x = 0;
	if (!s)
		return (0);
	lines.strs = malloc(sizeof(char *) * (ft_words(s, charset) + 1));
	if (!lines.strs)
		return (NULL);
	lines.strs = ft_lines(s, charset, &lines);
	if (lines.strs)
		lines.strs[ft_words(s, charset)] = 0;
	return (lines.strs);
}
