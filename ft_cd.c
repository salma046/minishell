#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
} 

int ft_cd(t_minishell data)
{
    while (data.tokens)
    {
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