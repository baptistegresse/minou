#include "../includes/minishell.h"
#include <string.h>

void	ft_print_env(t_env	**env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int i;
	char	*buffer = NULL;
	char	**cmds_split;

	data = malloc(sizeof(t_data));
	
	ft_parse_env(&data->head_env, envp);
	while (1) 
	{
		buffer = readline(">");
		printf("base :%s\n", buffer);
		cmds_split = ft_lexer(buffer, ' ');
		printf("lexer :");
		for (i = 0; cmds_split[i]; i++)
			printf("%s ,", cmds_split[i]);
		printf("\nexpand var :");
		cmds_split = ft_expand_var(&data->head_env, cmds_split);
		for (i = 0; cmds_split[i]; i++)
			printf("%s ,", cmds_split[i]);
		printf("\nexpand path :");
		cmds_split = ft_expand_path(&data->head_env, cmds_split);
		for (i = 0; cmds_split[i]; i++)
			printf("%s ,", cmds_split[i]);
		printf("\n");
	}


	return (0);	
}



