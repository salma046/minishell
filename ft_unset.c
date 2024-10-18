#include "minishell.h"

t_env ft_backup(t_env *original)
{
    t_env *tmp ;
    t_env *node ;
    t_env *node_last ;
    while (original != NULL )
    {
		t_env *node = (t_env *)malloc(sizeof(t_env));
		if (!node)
			exit(1);
    	printf("Aloha");
        printf("o:::::%s\n", original->key);
        printf("o:::::%s\n", original->value);
        free(original->key);
        free(original->value);
        tmp = original;
        original = original->next ;
        free(tmp);
    }
}
void 	ft_unset(t_env *env_list, t_minishell data)
{
	(void)data;
	(void)env_list;
	printf("\033[36m-------  I'm in the unset -------\033[0m \n");
	ft_backup(env_list);
}
// int p = ft_strcmp(data.envirement, cmd_env.key);
	
	
	// printf("%s\n", env_list->value);
	// printf("cmd_env.key :%s\n", cmd_env.key);
	// if (p == 0)
	// 	printf("The same");
	// else 
	// 	printf("Not the same");
