#include "../minishell.h"

void	ft_env(char **cmds, t_minishell *data)
{
	t_env	*tmp;

	tmp = data->envir;
	if (tmp && cmds[1] == NULL)
	{
		while (tmp)
		{
			if (tmp->value != NULL)
			{
				printf("%s", tmp->key);
				printf("%c", '=');
				printf("%s\n", tmp->value);
			}
			tmp = tmp->next;
		}
	}
	else
		fprintf(stderr, "env: %s: No such file or directory\n", cmds[1]);
}
