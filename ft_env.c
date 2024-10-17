// #include "minishell.h"

// void ft_env(t_minishell data)
// {
// 	(void)data;
// 	int i = 0;
// 	while(data.envirement[i] != NULL)
// 	{
// 		t_env cmd_env;
// 		char *equal_line = strchr(data.envirement[i], '=');
// 		printf("aloha\n");
// 		if(!equal_line)
// 		{
// 			printf("lll");
// 			cmd_env.key = strndup (data.envirement[i], equal_line - data.envirement[i]);
// 			printf("this is the key: %s", cmd_env.key);
// 		}
// 		i++;
// 	}
// }
#include "minishell.h"

void ft_env(t_minishell data)
{
    (void)data;
    int i = 0;
    while(data.envirement[i] != NULL)
    {
        t_env cmd_env;
        char *equal_env = strchr(data.envirement[i], '=');
        if (equal_env != NULL)
        {
			// printf("this is it:%s\n", equal_env);

            cmd_env.key = strndup(data.envirement[i], equal_env - data.envirement[i]);
            cmd_env.value = strndup(equal_env + 1, ft_strlen(data.envirement[i] + 1 ));
			cmd_env.equal = '=';
            printf("%s\n", cmd_env.key );
            printf("%s\n", cmd_env.value);
            printf("%c\n", cmd_env.equal);

        }
        // printf("-----> :%s\n", cmd_env.value);
        i++;
    }
}