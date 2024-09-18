/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:22:56 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/14 10:02:52 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remplace_str(char *data, int i, int count_quotes)
{
	int j = 0;
	char *word;
	char quote;

	j = count_quotes * 2;
	word = (char *)malloc(i - j + 1);
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
			while(data[i] && data[i] != quote)
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
	int i;
	int count_quotes;
	char quote;
	t_token	*temp_tokens;

	temp_tokens = tokens;

	while (temp_tokens)
	{
		i = 0;
		count_quotes = 0;
		if (temp_tokens->data_type == 0)
		{
			while (temp_tokens->data[i])
			{
				if (temp_tokens->data[i] == '\'' || temp_tokens->data[i] == '"')
				{
					quote = temp_tokens->data[i];
					count_quotes++;
					i++;
					while(temp_tokens->data[i] && temp_tokens->data[i] != quote)
						i++;
					if (temp_tokens->data[i] == quote)
						i++;
				}
				else if (temp_tokens->data[i] != '\0')
					i++;
			}
			if (count_quotes)
				temp_tokens->data = remplace_str(temp_tokens->data, i, count_quotes);
			// printf("the number of qotes is: %d\n", count_quotes);
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (tokens);
}
