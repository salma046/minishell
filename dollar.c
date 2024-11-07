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
			i++;
		if (str[i] == '$' && str[i + 1] == '$')
		{
			while (str[i + 1] == '$')
				i+=2;
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
				i++;
		}
	}
	return (j);
}

char	*remp_with_null(char *str)
{
	int i;
	int j;
	int t = 0;
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
			while (str[i] && str[i] != '"' && t != 1)
			{
				if (str[i] == '$' && str[i + 1] == '$')
				{
					while (str[i] == '$' && str[i + 1] == '$')
						i+=2;
				}
				if (str[i] != '$')
					word[j++] = str[i++];
				else
				t = 1;
			}
			if (str[i] == '"')
				word[j++] = str[i++];
		}
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$' && is_not_valid_expend(str, i) == 1)
			word[j++] = str[i++];
		if (str[i] != '\'' && str[i] != '"' && str[i] != '$' && str[i + 1] == '$')
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
	int t = 0;
	int	word_lenth;
	char *word;
	char *hi;
	char *command_rest;

	word_lenth = count_dollar_lenth(str);
	i = ft_strlen(str);
	k = ft_strlen(env_var);
	word = malloc(sizeof(char) * i - word_lenth + k + 1);
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	l = 0;
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
			while (str[i] && str[i] != '"' && t != 1)
			{
				if (str[i] == '$' && str[i + 1] == '$')
				{
					while (str[i] == '$' && str[i + 1] == '$')
						i+=2;
				}
				if (str[i] != '$')
					word[j++] = str[i++];
				else
				t = 1;
			}
			if (str[i] == '"')
				word[j++] = str[i++];
		}
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$' && is_not_valid_expend(str, i) == 1)
			word[j++] = str[i++];
		if (str[i] != '\'' && str[i] != '"' && str[i] != '$' && str[i + 1] == '$')
			word[j++] = str[i++];
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
			while (l < k)
				word[j++] = env_var[l++];
			l = i;
			while (str[i])
				i++;
			word[j] = '\0';
		}
		else if (str[i] && str[i] != '$' && str[i - 1] != '$' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	command_rest = after_dol_word(str, l, ft_strlen(str));
	hi = ft_strjoin(word, command_rest);
	free(command_rest);
	free(word);
	return (hi);
}

char	*remplace_doll_str(char	*data, char *env_var)
{
	char *word;
	if (env_var == NULL)
		return (remp_with_null(data));
	else
		word = remp_with_value(data, env_var);
	return (word);
}

char	*get_env_var(char *str, int i)
{
	char	*env_var;
	char	*env_value;
	int		j;
	int		temp;

	i++;
	temp = 0;
	j = i;
	while (str[i] == '$')
		i++;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
		i++;
	env_var = (char *)malloc(i - j + 1);
	if (!env_var)
		return (NULL);
	while (j < i)
		env_var[temp++] = str[j++];
	env_var[temp] = '\0';
	env_value = getenv(env_var);
	free(env_var);
	return (env_value ? env_value : NULL);
}

int is_not_alpanum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	else
		return (0);
}

char	*rmp_dollar(char *tokens_word, t_token **tokens_list)
{
	int i;
	int t = 0;
	char *env_var;
	int to_split = -1;

	i = 0;
	env_var = NULL;
	(void)tokens_list;
	while (tokens_word[i])
	{
		while (tokens_word[i] == '\'')
		{
			i++;
			while(tokens_word[i] && tokens_word[i] != '\'')
				i++;
			if (tokens_word[i] == '\'')
				i++;
		}
		if (tokens_word[i] == '"')
		{
			i++;
			to_split = -1;
			while (tokens_word[i] && tokens_word[i] != '"' && t != 1)
			{
				if (tokens_word[i] == '$' && tokens_word[i + 1] == '$')
				{
					while (tokens_word[i] == '$' && tokens_word[i + 1] == '$')
						i+=2;
				}
				if (tokens_word[i] != '$')
					i++;
				else
				{
					to_split = 1;
					t = 1;
				}
			}
			t = 0;
			if (tokens_word[i] == '"')
				i++;
		}
		else if (tokens_word[i] == '$' && tokens_word[i + 1] == '$')
		{
			while (tokens_word[i] == '$' && tokens_word[i + 1] == '$')
				i+=2;
			// double $$ without a valid or null env var stays the same
		}
		else if (tokens_word[i] == '$' && is_not_alpanum(tokens_word[i + 1]) == 0)
		{
			if (tokens_word[i] == '$')
				i++;
			while (tokens_word[i] && tokens_word[i] != '"' && tokens_word[i] != '\''&& tokens_word[i] != '$')
				i++;
		}
		else if (tokens_word[i] == '$')
		{
			env_var = get_env_var(tokens_word, i);
			if (env_var != NULL && check_4_space(env_var) == 1 && to_split < 0)
				tokens_word = token_edi_env(tokens_word, env_var, tokens_list);
			else
				tokens_word = remplace_doll_str(tokens_word, env_var);
			i = 0;
		}
		else if (tokens_word[i])
			i++;
	}
	return (tokens_word);
}
