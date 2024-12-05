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

void	ft_check_n_flag(t_token **tmp_tokens, int *flag)
{
	*flag = 0;
	while (*tmp_tokens && (*tmp_tokens)->next_token
		&& !ft_strcmp((*tmp_tokens)->next_token->data, "-n"))
	{
		*flag = 1;
		*tmp_tokens = (*tmp_tokens)->next_token;
	}
}

void	ft_echo(t_token *data)
{
	t_token *tmp_tokens;
	int flag;

	tmp_tokens = data;
	if (!tmp_tokens->data)
		return ;

	if (tmp_tokens->next_token == NULL)
	{
		write(1, "\n", 1);
		return ;
	}

	ft_check_n_flag(&tmp_tokens, &flag);

	if (tmp_tokens->next_token)
		tmp_tokens = tmp_tokens->next_token;
	else
		return ;

	ft_print(tmp_tokens);
	if (!flag)
		write(1, "\n", 1);
}