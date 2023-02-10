#include "../includes/minishell.h"

/*
	ft_quotes: This function handles quotes in the string. If the current character
	is a quote, it loops through the string until it finds the next matching quote.
*/

static void	ft_quotes(char const *s, int *j)
{
	if (s[(*j)] == '"')
	{
		(*j)++;
		while (s[(*j)] && s[(*j)] != '"')
			(*j)++;
	}
	else if (s[(*j)] == '\'')
	{
		(*j)++;
		while (s[(*j)] && s[(*j)] != '\'')
			(*j)++;
	}
}

/*
	ft_words: This function calculates the number of words 
	in the string using the given separator character.
*/

static int	ft_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		ft_quotes(s, &i);
		if (s[i] != c && s[i] != 0)
		{
			words++;
			i++;
		}
		while (s[i] && s[i] != c && s[i] != '"')
			i++;
	}
	return (words);
}

/*
	ft_dupstr: This function duplicates a givensubstring in the original string.
*/

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

/*
	ft_free_strs: This function frees the memory space allocated for the array of character strings.
*/

static char	**ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

/*
	ft_lines: This function splits the string into words and stores them in the string array.
	 It uses the ft_quotes function to handle quotes and ft_dupstr to duplicate words.
*/

static	char	**ft_lines(char const *s, char c, char **strs, int x)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		ft_quotes(s, &j);
		while (s[j] && s[j] != c)
		{
			j++;
			ft_quotes(s, &j);
		}
		if ((s[j] == c || !s[j]) && s[j - 1] != c)
		{
			strs[x] = ft_dupstr(s, i, j);
			if (strs[x] == 0)
				return (ft_free_strs(strs));
			x++;
			i = j;
		}
	}
	return (strs);
}

/*
	ft_lexer: This function is the entry point of the lexer. It allocates memory space for the array of strings,
	 calls ft_lines to split the string into words, and returns the array of strings.
*/

char	**ft_lexer(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (0);
	strs = malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!strs)
		return (NULL);
	strs = ft_lines(s, c, strs, 0);
	if (strs)
		strs[ft_words(s, c)] = 0;
	return (strs);
}
