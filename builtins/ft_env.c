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
			write(data.in_file, tmp->key, strlen(tmp->key));
			write(data.in_file, "=", 1);
			write(data.in_file, tmp->value, strlen(tmp->value));
			write(data.in_file, "\n", 1);
			// printf("%s", tmp->key);
			// printf("%c", '=');
			// printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
}
