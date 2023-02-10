#include "../includes/minishell.h"
#include <string.h>

char	**ft_cmds_split(char **cmds)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	char	**result;

	i = 0;
	j = 0;
	quote = 0;
	result = (char **)malloc(sizeof(char *) * strlen(*cmds));
	while (cmds[i])
	{
		k = 0;
		result[j] = (char *)malloc(sizeof(char) * ft_strlen(cmds[i]));
		for (int l = 0; cmds[i][l]; l++)
		{
			if (cmds[i][l] == '\"')
				quote = (quote == 0) ? 1 : 0;
			else if ((cmds[i][l] == '>' || cmds[i][l] == '<' || cmds[i][l] == '|') && quote == 0)
			{
				result[j][k] = '\0';
				j++;
				result[j] = (char *)malloc(sizeof(char));
				result[j][0] = cmds[i][l];
				result[j][1] = '\0';
				j++;
				k = 0;
				continue ;
			}
			result[j][k++] = cmds[i][l];
		}
		result[j][k] = '\0';
		j++;
		i++;
	}
	result[j] = 0;
	return (result);
}
