#include "../minishell.h"

char	*remplac_str(char *data, int i, int count_quotes)
{
	int		j;
	char	*word;
	char	quote;

	word = (char *)malloc(i - (count_quotes * 2) + 1);
	if (!word)
		return (NULL);
	j = 0;
	i = 0;
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '"')
		{
			quote = data[i];
			i++;
			while (data[i] && data[i] != quote)
				word[j++] = data[i++];
			if (data[i] == quote)
				i++;
		}
		else if (data[i] != '\0')
			word[j++] = data[i++];
	}
	word[j] = '\0';
	return (word);
}

t_token	*rm_qotes(t_token *tokens)
{
	int		i;
	int		n_quotes;
	char	quot;
	t_token	*temp_tokens;

	temp_tokens = tokens;
	while (temp_tokens)
	{
		i = 0;
		n_quotes = 0;
		if (temp_tokens->data_type == 0)
		{
			while (temp_tokens->data[i])
			{
				if (temp_tokens->data[i] == '\'' || temp_tokens->data[i] == '"')
				{
					quot = temp_tokens->data[i];
					n_quotes++;
					i++;
					while (temp_tokens->data[i] && temp_tokens->data[i] != quot)
						i++;
					if (temp_tokens->data[i] == quot)
						i++;
				}
				else if (temp_tokens->data[i] != '\0')
					i++;
			}
			if (n_quotes)
				temp_tokens->data = remplac_str(temp_tokens->data, i, n_quotes);
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (tokens);
}
