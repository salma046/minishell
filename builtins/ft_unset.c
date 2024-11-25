#include "../minishell.h"

// You need to free it .
void	ft_env_unset(t_minishell data)
{
	int		i;
	t_env	*head;
	t_env	*last_node;
	t_env	*cmd_env;
	char	*equal_env;

	printf(" \033[36m------------> %s  <---------\033[0m\n\n\n",
			data.tokens->data);
	if (data.tokens->next_token == NULL)
		return ;
	i = 0;
	head = NULL;
	last_node = NULL;
	while (data.envirement[i] != NULL)
	{
		cmd_env = (t_env *)malloc(sizeof(t_env));
		cmd_env->test = "TERM_SESSION_ID";
		if (!cmd_env)
			exit(1);
		equal_env = ft_strchr(data.envirement[i], '=');
		if (equal_env != NULL)
		{
			cmd_env->key = ft_strndup(data.envirement[i], equal_env
					- data.envirement[i]);
			cmd_env->value = ft_strndup(equal_env + 1, ft_strlen(data.envirement[i]
						+ 1));
			cmd_env->equal = '=';
			cmd_env->next = NULL;
		}
		if (last_node == NULL)
			head = cmd_env;
		else
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	// printf("HELLO WORLD\n");
	ft_backup(head, data); // now the head got updated when the unset executed
	t_env	*tmp;
	tmp = head;
	while (tmp)
	{
		tmp->test = data.tokens->next_token->data;
		printf("-->:%s", tmp->key);
		printf("<%c>", tmp->equal);
		printf("-->%s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	ft_unset(t_env *env_list, t_minishell data)
{
	(void)data;
	(void)env_list;
	printf("\033[36m-------  I'm in the unset -------\033[0m \n");
	ft_env_unset(data);
	printf("\033[0;33m-----------------------------\033[0m\n");
}
