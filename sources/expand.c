#include "../includes/minishell.h"

/* 
    The ft_replace_env function loops through a linked environment 
    list and returns the value corresponding to the given key. 
*/

static char *ft_replace_env(t_env **head, char *key)
{
	t_env	*current;

	printf("--%s--", key);
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
    The ft_expand function walks through the array of commands 
    and replaces found environment variables with their values ​​using ft_replace_env. 
*/

char	**ft_expand_var(t_env **head, char	**cmds)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (cmds[i])
	{
		temp = ft_strchr(cmds[i], '$');
		if (temp)
		{
			*temp = 0;
			j = 1;
			while (temp[j] && ft_isalnum(temp[j]))
				j++;
			cmds[i] = ft_strjoin(cmds[i], ft_replace_env(head, ft_substr(temp + 1, 0, j - 1)));
			while (temp[j] && ft_isalnum(temp[j]))
				j++;
			*temp = 0;
			j = 1;
			cmds[i] = ft_strjoin(cmds[i], ft_replace_env(head, ft_substr(temp + 1, 0, j - 1)));
		}
		i++;
	}
	return (cmds);
}
