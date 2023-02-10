#include "../includes/minishell.h"

/* 
    The ft_replace_env function loops through a linked environment 
    list and returns the value corresponding to the given key. 
*/

static char *ft_replace_env(t_env **head, char *key)
{
	t_env *current;
    
    current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return current->value;
		current = current->next;
	}
	return ft_strdup("");
}

/*
     The ft_in_squote function allowed if the string 
     passed as argument is between single quotes.
*/

static bool	ft_in_squote(char *string)
{
	int	i;
	int	j;

	i = 0;
	while (string[i] && string[i] != '$')
		i++;
	j = i;
	while (string[i] && string[i] != SQUOTE && string[i] != DQUOTE)
		i++;
	while (string[j] && string[j] != SQUOTE && string[j] != DQUOTE)
		j--;
	if (string[j] == SQUOTE && string[i] == SQUOTE)
		return (true);
	return (false);
}

/* 
    The ft_expand function walks through the array of commands 
    and replaces found environment variables with their values ​​using ft_replace_env. 
*/

char	**ft_expand(t_env **head, char	**cmds)
{
	int		i;
	int		j;
	char	*temp;
	char	*val;

	i = 0;
	while (cmds[i])
	{
		temp = ft_strchr(cmds[i], '$');
		while (temp && !ft_in_squote(cmds[i]))
		{
			j = 0;
			while (temp[j] != SPACE && temp[j] != SQUOTE && temp[j] != DQUOTE && temp[j])
				j++;
			val = ft_replace_env(head, ft_substr(temp, 1, j - 1));
			cmds[i] = ft_strjoin(ft_substr(cmds[i], 0, temp - cmds[i]), \
			ft_strjoin(val, ft_substr(temp, j, ft_strlen(temp) - j))); \
			temp = ft_strchr(cmds[i], '$');
		}
		i++;
	}
	return (cmds);
}
// $USER$USER ne marche pas