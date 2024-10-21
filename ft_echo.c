
#include "minishell.h"
void ft_print(t_minishell data)
{
    while (data.tokens)
    {
        write(1, data.tokens->data, ft_strlen(data.tokens->data));
        if (data.tokens->next_token != NULL)
            write(1, " ", 1);
        data.tokens = data.tokens->next_token;
    }
}

void ft_echo(t_minishell data)
{ 
    printf("         -> \033[0;31m Ana f echo\033[0m <-\n");
    if (data.tokens->data)
    {
        if (data.tokens->next_token == NULL)
        {
            write(1, "\n", 1);
            return;
        }
        if (!ft_strncmp(data.tokens->next_token->data , "-n",2))
        {
            data.tokens = data.tokens->next_token->next_token;
            if (data.tokens == NULL )
                return;
            ft_print(data);
        }
        else 
        {
            data.tokens = data.tokens->next_token;
            ft_print(data);
            write(1, "\n",1 );
        }
    }
}

                        