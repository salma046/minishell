/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:47:57 by salaoui           #+#    #+#             */
/*   Updated: 2024/10/07 19:16:57 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_not_valid_expend(char *str, int i);

int count_dollar_lenth(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] && str[i] != '\'' && is_not_valid_expend(str, i) == 1)
			i++;
		while (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		if (str[i] == '"')
		{
			while(str[i] != '$' && str[i] != '"')
				i++;
		}
		if (str[i] == '"')
			i++;
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$' && is_not_valid_expend(str, i) == 1)
		{
			i++;
			// j++;
		}
		if (str[i] == '$' && str[i + 1] == '$')
		{
			while (str[i + 1] == '$')
			{
				i+=2;
				// j+=2;
			}
		}
		if (str[i] == '$' && str[i + 1] != '$' && is_not_alpanum(str[i + 1]) == 1)
		{
			i++;
			j++;
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
			{
				i++;
				j++;
			}
			while(str[i])
			{
				i++;
				// j++;
			}
		}
	}
	return (j);
}

char	*remp_with_null(char *str)
{
	int i;
	int j;
	int	word_lenth;
	char *word;

	word_lenth = count_dollar_lenth(str);
	i = ft_strlen(str);
	word = malloc(sizeof(char) * i - word_lenth + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '\'')
		{
			word[j++] = str[i++];
			while (str[i] && str[i] != '\'')
				word[j++] = str[i++];
			if (str[i] == '\'')
				word[j++] = str[i++];
		}
		if (str[i] == '"')
		{
			word[j++] = str[i++];
			while (str[i] && str[i] != '$' && str[i] != '"')
				word[j++] = str[i++];
			if (str[i] == '"')
				word[j++] = str[i++];
		}
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$' && is_not_valid_expend(str, i) == 1)
			word[j++] = str[i++];
		if (str[i] == '$' && str[i + 1] == '$')
		{
			while (str[i] == '$' && str[i + 1] == '$')
				i+=2;
		}
		if (str[i] == '$' && str[i + 1] != '$' && is_not_alpanum(str[i + 1]) == 1)
		{
			i++;
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
				i++;
			while (str[i])
				word[j++] = str[i++];
			word[j] = '\0';
		}
	}
	word[j] = '\0';
	return(word);
}

char *after_dol_word(char *str, int l, int str_len)
{
	int j;
	char *word;

	word = malloc(sizeof(char) * str_len - l + 1);
	j = 0;
	while (str[l])
		word[j++] = str[l++];
	word[j] = '\0';
	return (word);
}

int is_not_valid_expend(char *str, int i)
{
	if (str[i] == '$' && is_not_alpanum(str[i + 1]) == 1)
		return (0);
	else
		return (1);
}

char	*remp_with_value(char *str, char *env_var)
{
	int i;
	int j;
	int l;
	int k;
	int	word_lenth;
	char *word;
	char *hi;
	char *command_rest;

	word_lenth = count_dollar_lenth(str);
	i = ft_strlen(str);
	k = ft_strlen(env_var);
	word = malloc(sizeof(char) * i - word_lenth + k + 1);
	printf("the size alllocated is: %d and i is: %d word is: %d\n", i - word_lenth + k + 1, i, word_lenth);
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	l = 0;
	printf("the sting is: %s\n", str);
	while (str[i])
	{
		while (str[i] == '\'')
		{
			word[j++] = str[i++];
			while (str[i] && str[i] != '\'')
				word[j++] = str[i++];
			if (str[i] == '\'')
				word[j++] = str[i++];
		}
		if (str[i] == '"')
		{
			word[j++] = str[i++];
			while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\'')
				word[j++] = str[i++];
			if (str[i] == '"')
				word[j++] = str[i++];
		}
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$' && is_not_valid_expend(str, i) == 1)
		{
			word[j++] = str[i++];
		}
		if (str[i] == '$' && str[i + 1] == '$')
		{
			while (str[i] == '$' && str[i + 1] == '$')
				i+=2;
		}
		if (str[i] && str[i] == '$' && str[i + 1] != '$' && is_not_alpanum(str[i + 1]) == 1)
		{
			i++;
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
				i++;
			while (l <= k)
			{
				word[j++] = env_var[l++];
			}
			l = i;
			while (str[i])
				i++;
			word[j] = '\0';
			printf("the word should be 'salaoui' it is: %s\n", word);
		}
		else if (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	command_rest = after_dol_word(str, l, ft_strlen(str));
	hi = ft_strjoin(word, command_rest);
	printf("after joining it is: %s\n", hi);
	free(word);
	return (hi);
}

char	*remplace_doll_str(char	*data, char *env_var)
{
	if (env_var == NULL)
		return (remp_with_null(data));
	else 
	{
		char *word = remp_with_value(data, env_var);
		return (word);
	}
}

char	*get_env_var(char *str, int i)
{
	char *env_var;
	i++;
	int j = i;

	int temp = 0;
	while (str[i] == '$')
	{
		i++;
	}
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
		i++;
	env_var = (char *)malloc(i - j + 1);
	while (j < i)
		env_var[temp++] = str[j++];
	env_var[temp] = '\0';
	if (getenv(env_var) == NULL)
	{
		free(env_var);
		return (NULL);
	}
	else
	{
		char *hello = getenv(env_var);
		return (getenv(env_var));
	}
	
}

int is_not_alpanum(char c)
{
	if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')
		return (1);
	else
		return (0);
}

t_token	*rmp_dollar(t_token *tokens)
{
	int i;
	char *env_var;
	t_token	*temp_tokens;

	temp_tokens = tokens;
	i = 0;
	while (temp_tokens)
	{
		env_var = NULL;
		if (temp_tokens->data_type == 2 && temp_tokens->next_token && temp_tokens->next_token->data_type == 0)
		{
			temp_tokens = temp_tokens->next_token;
			while (temp_tokens->data[i])
				i++;
			i = 0;
		}
		else if (temp_tokens->data_type == 0)
		{
			while (temp_tokens->data[i])
			{
				while (temp_tokens->data[i] == '\'')
				{
					i++;
					while(temp_tokens->data[i] && temp_tokens->data[i] != '\'')
						i++;
					if (temp_tokens->data[i] == '\'')
						i++;
				}
				if (temp_tokens->data[i] == '"')
				{
					i++;
					while (temp_tokens->data[i] && temp_tokens->data[i] != '$' && temp_tokens->data[i] != '\'' && temp_tokens->data[i] != '"')
						i++;
					if (temp_tokens->data[i] == '"')
						i++;
				}
				else if (temp_tokens->data[i] == '$' && temp_tokens->data[i + 1] == '$')
				{
					while (temp_tokens->data[i] == '$' && temp_tokens->data[i + 1] == '$')
						i+=2;
				}
				else if (temp_tokens->data[i] == '$' && is_not_alpanum(temp_tokens->data[i + 1]) == 0)
				{
					if (temp_tokens->data[i] == '$')
						i++;
					while (temp_tokens->data[i] && temp_tokens->data[i] != '"' && temp_tokens->data[i] != '\''&& temp_tokens->data[i] != '$')
						i++;
				}
				else if (temp_tokens->data[i] == '$')
				{
					env_var = get_env_var(temp_tokens->data, i);
					// printf("the word is: %s\n", env_var);
					temp_tokens->data = remplace_doll_str(temp_tokens->data, env_var);
					i = 0;
				}
				else if (temp_tokens->data[i])
					i++;
			}
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (tokens);
}
