
#include "../minishell.h"

// hnaya dert wahed l copy l env bax n9der n9arenha m3a l key w nchof xno radi i5sni n delete

void	ft_backup(t_env *original, t_minishell data)
{
	t_env	*tmp;

	while (original != NULL)
	{
		original->test = data.tokens->next_token->data;
		printf("\033[0;31m %s \033[0m", original->test);
		printf("\033[0;33m|---------------|||||||||||||--------------|\033[0m\n");
		printf("-->:::::%s\n", original->key);
		printf("-->:::::%s\n", original->value);
		// I need to add first the riginal->test than remove it
		if (original->test != NULL && !ft_strcmp(original->key, original->test))
		{
			free(original->key);
			printf("\033[36m   /\\  \033[0m \n"); 
				// First line with forward slash and backslash
			printf("\033[36m  /  \\ \033[0m \n");  // Second line
			printf("\033[36m /    \\\033[0m \n");  // Third line
			printf("\033[36m |  *  | \033[0m \n"); // star line
			printf("\033[36m \\    /\033[0m \n"); 
				// Fourth line with backslash and forward slash
			printf("\033[36m  \\  / \033[0m \n");  // Fifth line
			printf("\033[36m   \\/  \033[0m \n");
		}
		printf("\033[0;33m|-----------------------------|\033[0m\n");
		free(original->key);
		free(original->value);
		tmp = original;
		original = original->next;
		free(tmp);
	}
}
// I called the function normaly of env.
void	ft_env(t_minishell data)
{
	int i = 0;
	t_env *last_node = NULL;

	while (data.envirement[i] != NULL)
	{
		t_env *cmd_env = (t_env *)malloc(sizeof(t_env));
		if (!cmd_env)
			exit(1);
		char *equal_env = strchr(data.envirement[i], '=');
		if (equal_env != NULL)
		{
			cmd_env->key = strndup(data.envirement[i], equal_env
					- data.envirement[i]);
			cmd_env->value = strndup(equal_env + 1, ft_strlen(data.envirement[i]
						+ 1));
			cmd_env->equal = '=';
			cmd_env->next = NULL;
			printf("%s", cmd_env->key);
			printf("%c", cmd_env->equal);
			printf("%s\n", cmd_env->value);
		}
		if (last_node != NULL)
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	// if (next node is an key than call this fnc) /// test: env KEY as argumen
	// ft_backup(last_node, data);
}