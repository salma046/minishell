#include "minishell.h"

void ft_sd(t_token *data)
{
	t_token	*temp_tokens;

	temp_tokens = data;
	if (!ft_strcmp(temp_tokens->data , "echo"))
    {
		printf("Hnaya radi in executiw l command dyali");
	}
}