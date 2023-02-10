#include "../includes/minishell.h"

#include <string.h>

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	char	**salut;

	salut = malloc(sizeof(char *) * 3);
	salut[0] = "salu | bonjour sfdsfd";
	salut[1] = "$USER";
	salut[2] = NULL;

	data = malloc(sizeof(t_data));

	ft_parse_env(&data->head_env, envp);
	char	**test = ft_expand(&data->head_env, salut);
	// char	**root = ft_cmds_split(test);

	printf("%s\n", root[0]);
	printf("%s", root[1]);

	return (0);	
}



