#include "../minishell.h"

void	ft_print(t_token *tokens)
{
	t_token	*tmp_token;

	tmp_token = tokens;
	while (tmp_token)
	{
		write(1, tmp_token->data, ft_strlen(tmp_token->data));
		if (tmp_token->next_token != NULL)
			write(1, " ", 1);
		tmp_token = tmp_token->next_token;
	}
}

void	ft_echo(t_token *data)
{
	t_token	*tmp_tokens;

	tmp_tokens = data;
	printf("         -> \033[0;31m Ana f echo\033[0m <-\n");
	if (tmp_tokens->data)
	{
		if (tmp_tokens->next_token == NULL)
		{
			write(1, "\n", 1);
			return ;
		}
		if (!ft_strncmp(tmp_tokens->next_token->data, "-n", 2))
		{
			tmp_tokens = tmp_tokens->next_token->next_token;
			if (tmp_tokens == NULL)
				return ;
			ft_print(data);
		}
		else
		{
			tmp_tokens = tmp_tokens->next_token;
			ft_print(tmp_tokens);
			write(1, "\n", 1);
		}
	}
}
