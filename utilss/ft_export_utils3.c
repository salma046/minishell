#include "../minishell.h"

int	check_key(char *str, t_env *envir)
{
	t_env	*temp_env;

	temp_env = envir;
	while (temp_env)
	{
		if (!ft_strcmp(temp_env->key, str))
			return (1);
		temp_env = temp_env->next;
	}
	return (0);
}

void	key_without_equal(char *data, t_env *envir)
{
	t_env	*head;
	t_env	*new_export;

	head = NULL;
	head = envir;
	while (head && head->next != NULL)
		head = head->next;
	if (check_key(data, envir) == 0)
	{
		new_export = (t_env *)malloc(sizeof(t_env));
		if (!new_export)
			exit(1);
		new_export->key = ft_strdup(data);
		new_export->value = NULL;
		new_export->next = NULL;
		if (head == NULL)
			envir = new_export;
		else
			head->next = new_export;
		head = new_export;
	}
}

// export alone
void	sort_env(t_env *envir)
{
	t_env	*new_env;
	char	*tmp_key;
	char	*tmp_value;

	if (envir == NULL || envir->next == NULL)
		return ;
	new_env = envir->next;
	while (new_env)
	{
		if (ft_strcmp(envir->key, new_env->key) > 0)
		{
			tmp_key = envir->key;
			envir->key = new_env->key;
			new_env->key = tmp_key;
			tmp_value = envir->value;
			envir->value = new_env->value;
			new_env->value = tmp_value;
		}
		new_env = new_env->next;
	}
	sort_env(envir->next);
}


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
		if (token[i + 1] != '\0' && is_special_char(token[i])
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

void	key_with_equal(char *data, t_env *envir)
{
	t_env	*head;
	t_env	*new_export;
	char	*split_var;

	head = NULL;
	head = envir;
	while (head && head->next != NULL)
	{
		head = head->next;
	}
	split_var = ft_strchr(data, '=');
	new_export = malloc(sizeof(t_env));
	if (!new_export)
		return ;
	new_export->key = ft_strndup(data, split_var - data);
	new_export->value = put_quot2_value(ft_strdup(split_var + 1));
	new_export->next = NULL;
	if (head == NULL)
		envir = new_export;
	else
		head->next = new_export;
	head = new_export;
}

int	not_valid(char *str)
{
	if (ft_strcmp(str, "=") == 0 || str[0] == '=' || ft_isdigit(str[0])
		|| is_special_char(str[0]) || has_doubled_special_chars(str))
		return (1);
	else
		return (0);
}

void	process_key(char *data, t_env *expo_envir, t_env *env_envir)
{
	char	*split_var;
	char	*key;

	split_var = ft_strchr(data, '=');
	if (!split_var)
		key_without_equal(data, expo_envir);
	else
	{
		key = ft_strndup(data, split_var - data);
		if (check_key(key, expo_envir))
		{
			remove_node(&expo_envir, key);
			remove_node(&env_envir, key);
		}
		free(key);
		key_with_equal(data, expo_envir);
	}
}

int	search_special_char(char *token_data, t_node *node)
{
	int	i;

	(void)node;
	i = 0;
	while (token_data[i] != '\0' && token_data[i] != '=')
	{
		if (is_special_char(token_data[i]))
		{
			write(STDERR_FILENO, "bash: export: ", ft_strlen("bash: export: "));
			write(STDERR_FILENO, token_data, ft_strlen(token_data));
			write(STDERR_FILENO, "': not a valid identifier",
				ft_strlen("': not a valid identifier"));
			write(STDERR_FILENO, "\n", 1);
			// printf("bash: export: %s': not a valid identifier\n",
			// 	token_data);// use the write and in the fd;;;;;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_tokens(char **args, t_node *nodes)
{
	char	**tmp_args;
	int		i;

	i = 0;
	tmp_args = args;
	while (tmp_args[i])
	{
		if (search_special_char(tmp_args[i], nodes) == 1)
			return (1);
		i++;
	}
	return (0);
}