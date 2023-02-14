#include "../includes/minishell.h"


char *ft_replace_all_substrings(const char *string, const char *substring, const char *replacement) {
    const size_t substring_len = strlen(substring);
    const size_t replacement_len = strlen(replacement);
    const char *match;
    const char *start = string;
    size_t out_len = 1;

    // Compute the length of the output string
    while ((match = strstr(start, substring))) {
        out_len += (match - start) + replacement_len;
        start = match + substring_len;
    }
    out_len += strlen(start);

    // Allocate memory for the output string
    char *out = malloc(out_len);
    if (!out) {
        return NULL;
    }

    // Copy the input string to the output string, replacing all occurrences of the substring
    char *pos = out;
    start = string;
    while ((match = strstr(start, substring))) {
        size_t len = match - start;
        memcpy(pos, start, len);
        pos += len;
        memcpy(pos, replacement, replacement_len);
        pos += replacement_len;
        start = match + substring_len;
    }
    strcpy(pos, start);

    return out;
}

char	**ft_expand_path(t_env **head, char **cmds)
{
	int		i;
	t_env	*current;

	i = 0;
	current = *head;
	while(current && !ft_strstr(current->key, "HOME"))
		current = current->next;
	while (cmds[i])
	{
		if (ft_strstr(cmds[i], "~"))
			cmds[i] = ft_replace_all_substrings(cmds[i], "~", current->value);
		i++;
	}
	return (cmds);
}

char	**ft_expand_var(t_env **head, char	**cmds)
{
	int		i;
	t_env	*current;

	i = 0;
	while (cmds[i])
	{
		current = *head;
		while (current)
		{
			if (ft_strstr(cmds[i], "$"))
				cmds[i] = ft_replace_all_substrings(cmds[i], current->key, current->value);
			current = current->next;
		}
		i++;
	}
	return (cmds);
}
