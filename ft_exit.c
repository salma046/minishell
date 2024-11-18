#include "minishell.h"

void	ft_exit(t_token *data)
{
	t_token *tmp_tokens;

	tmp_tokens = data;
	int exit_status;

	exit_status = 0;
	if (tmp_tokens->next_token)
	{
		exit_status = ft_atoi(tmp_tokens->next_token->data);
		printf("%d", exit_status);
	}
	exit(exit_status);
}