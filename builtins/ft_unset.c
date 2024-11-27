#include "../minishell.h"

void	removeNode(t_env **head, char *keyToRemove)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (!ft_strcmp(keyToRemove, current->key))
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

// You need to free it .
t_env	*ft_env_unset(t_minishell data)
{
	t_env	*tmp;
	char	*test;
	t_token	*temp_tokens;

	tmp = data.envir;
	temp_tokens = data.tokens->next_token;
	if (data.tokens->next_token == NULL)
		return (tmp);
	while (temp_tokens && temp_tokens->data_type == WORD)
	{
		test = temp_tokens->data;
		tmp = data.envir;
		printf("the test word is: %s\n", test);
		while (tmp)
		{
			if (tmp->next != NULL && !ft_strcmp(test, tmp->next->key))
			{
				removeNode(&data.envir, test);
			}
			tmp = tmp->next;
		}
		temp_tokens = temp_tokens->next_token;
	}
	// to_checkk = data.envir;
	// while (to_checkk)
	// {
	// 	to_checkk->test = temp_tokens->next_token->data;
	// 	// printf("\nJust to check that test is LESS ->: %s\n", tmp->test);
	// 	printf("kkkkkkkkk:%s", to_checkk->key);
	// 	printf("<%c>", to_checkk->equal);
	// 	printf("-->%s\n", to_checkk->value);
	// 	to_checkk = to_checkk->next;
	// }
	return (tmp);
}

t_env	*ft_env_unset_for_export(t_minishell data)
{
	t_env	*tmp;
	char	*test;
	t_token	*temp_tokens;

	tmp = data.export_env;
	temp_tokens = data.tokens->next_token;
	if (data.tokens->next_token == NULL)
		return (tmp);
	while (temp_tokens && temp_tokens->data_type == WORD)
	{
		test = temp_tokens->data;
		tmp = data.export_env;
		printf("the test word is: %s\n", test);
		while (tmp)
		{
			if (tmp->next != NULL && !ft_strcmp(test, tmp->next->key))
			{
				removeNode(&data.export_env, test);
			}
			tmp = tmp->next;
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (tmp);
}

void	ft_unset(t_env *env_list, t_minishell data)
{
	(void)data;
	(void)env_list;
	printf("\033[36m-------  I'm in the unset -------\033[0m \n");
	data.envir = ft_env_unset(data);
	data.export_env = ft_env_unset_for_export(data);
	printf("\033[0;33m-----------------------------\033[0m\n");
}
