
#include "minishell.h"

// void ft_backup(t_env *original)
// {
//     t_env *tmp ;
    
//     while (original != NULL )
//     {
//         printf("o:::::%s\n", original->key);
//         printf("o:::::%s\n", original->value);
//         free(original->key);
//         free(original->value);
//         tmp = original;
//         original = original->next ;
//         free(tmp);
//     }
// }

void ft_env(t_minishell data)
{
    int i = 0;
    t_env *head = NULL;
    t_env *last_node = NULL;
    
    while(data.envirement[i] != NULL)
    {
        t_env *cmd_env = (t_env *)malloc(sizeof(t_env));
        if (!cmd_env)
            exit(1);
        char *equal_env = strchr(data.envirement[i], '=');
        if (equal_env != NULL)
        {
            cmd_env->key = strndup(data.envirement[i], equal_env - data.envirement[i]);
            cmd_env->value = strndup(equal_env + 1, ft_strlen(data.envirement[i] + 1 ));
			cmd_env->equal = '=';
			cmd_env->next = NULL;
            // printf("%s", cmd_env->key);
            // printf("%c", cmd_env->equal);
            // printf("%s\n", cmd_env->value);
            // free(cmd_env->key);
            // free(cmd_env->value);
        }
        if( last_node == NULL)
            head = cmd_env;
        else
            last_node->next = cmd_env;
        last_node = cmd_env;
        i++;
    }
    ft_backup(head);
}