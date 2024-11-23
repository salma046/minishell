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
int	count_quotes(char *data, int *len)
{
	int		count;
	char	quote;

	count = 0;
	*len = 0;
	while (data[*len])
	{
		if (data[*len] == '\'' || data[*len] == '"')
		{
			quote = data[(*len)++];
			count++;
			while (data[*len] && data[*len] != quote)
				(*len)++;
			if (data[*len] == quote)
				(*len)++;
		}
		else
			(*len)++;
	}
	return (count);
}

t_token	*rm_qotes(t_token *tokens)
{
	int		len;
	int		n_quotes;
	t_token	*temp_tokens;

	temp_tokens = tokens;
	while (temp_tokens)
	{
		if (temp_tokens->data_type == 0)
		{
			n_quotes = count_quotes(temp_tokens->data, &len);
			if (n_quotes)
				temp_tokens->data = remplac_str(temp_tokens->data,
						len, n_quotes);
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (tokens);
}
