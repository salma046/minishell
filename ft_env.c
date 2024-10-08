#include "minishell.h"

void ft_env(t_minishell data)
{
	(void)data;
	int i = 0;
	char *var_env = data.envirement[i];
	while(var_env != NULL)
	{
		printf("%s\n", data.envirement[i]);
		i++;
		var_env = data.envirement[i];
	}
}