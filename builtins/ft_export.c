#include "../minishell.h"

void	sort_env(t_senv *node)
{
	t_senv	*next_node;
	char	*tmp_key;
	char	*tmp_value;

	if (node == NULL || node->next == NULL)
		return ;
	next_node = node->next;
	while (next_node)
	{
		if (ft_strcmp(node->skey, next_node->skey) > 0)
		{
			tmp_key = node->skey;
			node->skey = next_node->skey;
			next_node->skey = tmp_key;
			tmp_value = node->svalue;
			node->svalue = next_node->svalue;
			next_node->svalue = tmp_value;
		}
		next_node = next_node->next;
	}
	sort_env(node->next);
}

void	ft_env_export_once(t_token *data, char **env, int active)
{
	t_senv	*head;
	t_senv	*last_node;
	int		i;
	t_senv	*cmd_env;
	char	*equal_env;
	t_senv	*current;

	(void)data;
	head = NULL;
	last_node = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		cmd_env = (t_senv *)malloc(sizeof(t_senv));
		if (!cmd_env)
			exit(1);
		equal_env = strchr(env[i], '=');
		if (equal_env != NULL)
		{
			cmd_env->skey = strndup(env[i], equal_env - env[i]);
			cmd_env->svalue = strndup(equal_env + 1, strlen(env[i] + 1));
			cmd_env->sequal = '=';
			cmd_env->next = NULL;
		}
		if (last_node == NULL)
			head = cmd_env;
		else
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	if (active == 1)
		sort_env(head);
	current = head;
	while (current)
	{
		if (active == 1)
			printf("declare -x %s=%s\n", current->skey, current->svalue);
		current = current->next;
	}
}
int	ft_check(char **env, char *key, char *value, int active)
{
	int		i;
	size_t	key_len;
	size_t	new_len;

	i = 0;
	active = 0;
	if (!env || !key || !value)
		return (0);
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			active = 1;
			free(env[i]);
			new_len = key_len + ft_strlen(value) + 2;
			env[i] = malloc(new_len);
			if (!env[i])
			{
				perror("malloc");
				return (1);
			}
			ft_strlcpy(env[i], key, new_len);
			ft_strlcat(env[i], "=", new_len);
			ft_strlcat(env[i], value, new_len);
			return (0);
		}
		i++;
	}
	return (0);
}
void	ft_add_to_export_arg(t_token *tokens, char **env)
{
	t_token	*current_token;
	t_env	*expo;
	char	*token_data;
	char	*splitVar;
	size_t	len;
	char	*new_env_str;
	int		i;
	int		active;

	active = 0;
	if (!tokens || !tokens->next_token || !env)
		return ;
	current_token = tokens->next_token;
	while (current_token != NULL)
	{
		token_data = current_token->data;
		if (ft_strcmp(token_data, "=") == 0)
		{
			printf("bash: export: `%s': not a valid identifier\n", token_data);
			current_token = current_token->next_token;
			continue ;
		}
		if (token_data[0] == '=')
		{
			printf("bash: export: `%s': not a valid identifier\n", token_data);
			current_token = current_token->next_token;
			continue ;
		}
		if (ft_isdigit(token_data[0]))
		{
			printf("bash: export: `%s': not a valid identifier\n", token_data);
			current_token = current_token->next_token;
			continue ;
		}
		expo = malloc(sizeof(t_env));
		if (!expo)
		{
			perror("malloc");
			return ;
		}
		splitVar = ft_strchr(token_data, '=');
		if (!splitVar)
		{
			free(expo);
			current_token = current_token->next_token;
			continue ;
		}
		expo->key = ft_strndup(token_data, splitVar - token_data);
		expo->value = ft_strdup(splitVar + 1);
		if (!expo->key || !expo->value)
		{
			free(expo->key);
			free(expo->value);
			free(expo);
			current_token = current_token->next_token;
			continue ;
		}
		i = 0;
		while (env[i] != NULL)
			i++;
		len = ft_strlen(expo->key) + ft_strlen(expo->value) + 2;
		new_env_str = malloc(len);
		if (!new_env_str)
		{
			free(expo->key);
			free(expo->value);
			free(expo);
			current_token = current_token->next_token;
			continue ;
		}
		ft_strlcpy(new_env_str, expo->key, len);
		ft_strlcat(new_env_str, "=", len);
		ft_strlcat(new_env_str, expo->value, len);
		if (!ft_check(env, expo->key, expo->value, active))
		{
			printf("\033[0;33m-------->HAdi raha %d<----------\033[0m", active);
		}
		env[i] = new_env_str;
		env[i + 1] = NULL;
		free(expo->key);
		free(expo->value);
		free(expo);
		current_token = current_token->next_token;
	}
}

void	ft_export(t_token *tokens, t_env *envir, char **env)
{
	int	active;

	(void)envir;
	if (!tokens || !env)
		return ;
	active = 1;
	if (tokens->next_token == NULL)
	{
		ft_env_export_once(tokens, env, active);
	}
	else
	{
		active = 0;
		ft_add_to_export_arg(tokens, env);
		ft_env_export_once(tokens, env, active);
	}
}
