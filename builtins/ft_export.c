#include "../minishell.h"

int	is_special_char(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64))
		return (1);
	if ((c >= 91 && c <= 96) || (c >= 123 && c <= 126))
		return (1);
	return (0);
}

int	has_doubled_special_chars(char *token)
{
	int	i;

	if (!token)
		return (0);
	i = 0;
	while (token[i] != '\0' && token[i] != '=')
	{
		if (token[i + 1] != '\0'
			&& is_special_char(token[i])
			&& is_special_char(token[i + 1]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*put_quot2_value(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!result)
		return (NULL);
	result[j++] = '"';
	while (str[i])
		result[j++] = str[i++];
	result[j] = '"';
	result[++j] = '\0';
	free(str);
	return (result);
}

void	key_with_equal(t_token *tokens, t_env *envir)
{
	t_env	*head;
	t_token	*temp_tokens;
	t_env	*new_export;
	char	*split_var;

	head = NULL;
	head = envir;
	while (head && head->next != NULL)
	{
		head = head->next;
	}
	temp_tokens = tokens;
	split_var = ft_strchr(temp_tokens->data, '=');
	new_export = malloc(sizeof(t_env));
	if (!new_export)
		return ;
	if (!split_var)
	{
		printf("Error: '=' not found in token_data.\n");
		free(new_export);
		return ;
	}
	new_export->key = ft_strndup(temp_tokens->data, split_var
			- temp_tokens->data);
	new_export->value = put_quot2_value(ft_strdup(split_var + 1));
	new_export->next = NULL;
	if (head == NULL)
		envir = new_export;
	else
		head->next = new_export;
	head = new_export;
}

int not_valid(char *str)
{
    if (ft_strcmp(str, "=") == 0 || str[0] == '='
		|| ft_isdigit(str[0]) || is_special_char(str[0])
		|| has_doubled_special_chars(str))
        return (1);
    else
        return (0);
}

void	ft_add_to_export_arg(t_token *tokens, t_env *expo_envir,
		t_env *env_envir)
{
	t_token	*current_token;
	char	*token_data;
	char	*split_var;
    char    *key;
	int		i;

	if (!tokens || !tokens->next_token || !expo_envir)
		return ;
	current_token = tokens->next_token;
	while (current_token != NULL && current_token->data_type == WORD)
	{
		token_data = current_token->data;
		if (!token_data)
		{
			current_token = current_token->next_token;
			continue ;
		}
		if (not_valid(token_data) == 1)
		{
			printf("bash: export: %s': not a valid identifier\n", token_data);
			current_token = current_token->next_token;
			continue ;
		}
		i = 0;
		while (token_data[i] != '\0' && token_data[i] != '=')
		{
			if (is_special_char(token_data[i]))
			{
				printf("bash: export: %s': not a valid identifier\n",
					token_data);
				current_token = current_token->next_token;
				break ;
			}
			i++;
		}
		if (token_data[i] != '\0' && token_data[i] != '=')
			continue ;
		split_var = ft_strchr(token_data, '=');
		if (!split_var)
			key_without_equal(current_token, expo_envir, 0);
		else
		{
            key = ft_strndup(token_data, split_var - token_data);
			if (check_key(key, expo_envir) == 1)
			{
				removeNode(&expo_envir, key);
				removeNode(&env_envir, key);
			}
			key_with_equal(current_token, expo_envir);
		}
		current_token = current_token->next_token;
	}
}

void	ft_export(t_token *tokens, t_env *expo_envir, t_env *env_envir)
{
	int	active;

	active = 0;
	(void)env_envir;
	if (!tokens || !expo_envir)
		return ;
	active = 1;
	if ((tokens->next_token == NULL && tokens->data))
	{
		if (tokens->prev_token && !ft_strcmp(tokens->prev_token->data,
				"export"))
			return ;
		ft_env_export_once(tokens, expo_envir, active);
	}
	else
	{
		active = 0;
		ft_add_to_export_arg(tokens, expo_envir, env_envir);
		printf("\n---2---\n");
	}
	search_check_add_env(expo_envir, env_envir);
}
