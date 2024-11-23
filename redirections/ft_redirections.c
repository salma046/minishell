#include "../minishell.h"

int	ft_check_redirections(t_minishell *data, t_token *tokens)
{
	t_token *current = tokens;
	(void)data;
	while (current)
	{
		if (current->data_type == INP_REDIR) //  <
		{
			if (ft_input(tokens) < 0)
				return (-1);
		}
		else if (current->data_type == OUT_REDIR) // >
		{
			if (ft_output(tokens) < 0)
				return (-1);
		}
		else if (current->data_type == APPEND) // >>
		{
			if (ft_append(tokens) < 0)
				return (-1);
		}
		current = current->next_token;
	}

	return (0);
}