#include "../minishell.h"

// I called the function normaly of env.
void	ft_env(t_minishell data)
{
	t_env	*tmp;
	tmp = data.envir;
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
