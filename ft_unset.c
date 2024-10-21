#include "minishell.h"

// You need to free it .
void ft_env_unset(t_minishell data)
{
	printf(" \033[36m------------> %s  <---------\033[36m\n\n\n\n", data.tokens->data );

    int i = 0;
    t_env *head = NULL;
    t_env *last_node = NULL;
    while(data.envirement[i] != NULL)
    {
        t_env *cmd_env = (t_env *)malloc(sizeof(t_env));
    	cmd_env->test = "TERM_SESSION_ID";
        if (!cmd_env)
            exit(1);
        char *equal_env = strchr(data.envirement[i], '=');
        if (equal_env != NULL)
        {
            cmd_env->key = strndup(data.envirement[i], equal_env - data.envirement[i]);
            cmd_env->value = strndup(equal_env + 1, ft_strlen(data.envirement[i] + 1 ));
			cmd_env->equal = '=';
			cmd_env->next = NULL;
        }
        if( last_node == NULL)
            head = cmd_env;
        else
            last_node->next = cmd_env;
        last_node = cmd_env;
        i++;
    }
	ft_backup(head, data);
}

void 	ft_unset(t_env *env_list, t_minishell data)
{
	(void)data;
	(void)env_list;
	printf("\033[36m-------  I'm in the unset -------\033[0m \n");
	ft_env_unset(data);
	printf("\033[0;33m-----------------------------\033[0m\n");
}

