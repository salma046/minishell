#include "minishell.h"

void ft_exit(t_minishell data)
{
	int exit_status;

	exit_status = 0;
	if(data.tokens->next_token)
	{
		exit_status = ft_atoi(data.tokens->next_token->data);
		printf("%d", exit_status);
	}
	exit(exit_status);
}