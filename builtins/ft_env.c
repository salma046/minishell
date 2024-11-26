#include "../minishell.h"

// I called the function normaly of env.
void	ft_env(t_minishell data)
{
	t_env	*tmp;
	tmp = data.envir;
	while (tmp)
	{
		// tmp->test = data.tokens->next_token->data;
		if (tmp->value != NULL)
		{
			printf("%s", tmp->key);
			printf("%c", tmp->equal);
			printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
}
