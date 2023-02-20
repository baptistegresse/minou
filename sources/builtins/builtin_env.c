#include "../../includes/minishell.h"

void	ft_builtin_env(t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
