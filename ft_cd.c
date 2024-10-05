#include "minishell.h"
// t_minishell g_minishell;

int ft_cd(t_minishell data)
{
    while (data.tokens)
    {
        if (!ft_strcmp(data.tokens->data, "cd") && data.tokens->next_token == NULL)
        {
            if (chdir(getenv("HOME")) == -1)
                perror("cd");
            printf("Home path:  \033[0;31m%s\033[0m\n", getenv("HOME"));
        }
        if (!ft_strcmp(data.tokens->data, "cd") && data.tokens->data)
        {
            printf("This is the path of cd:%s\n",getenv("HOME"));
            if (data.tokens->next_token && chdir(data.tokens->next_token->data) == -1)
                perror("\033[32m ERROR\033[0m");
            else
                printf("DONE ✅\n");
        }
        data.tokens = data.tokens->next_token;
    }
    return 0;
}