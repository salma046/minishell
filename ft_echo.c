
#include "minishell.h"
void ft_print(t_token *tokens)
{
    t_token tmp_token;
    tmp_token = *tokens;
    while (tmp_token)
    {
        write(1, tmp_token->data, ft_strlen(tmp_token.data));
        if (tmp_token.next_token != NULL)
            write(1, " ", 1);
        tmp_token = tmp_token.next_token;
    }
}

void ft_echo(t_token tokens)
{ 
    printf("         -> \033[0;31m Ana f echo\033[0m <-\n");
    if (tokens.data)
    {
        if (tokens.next_token == NULL)
        {
            write(1, "\n", 1);
            return;
        }
        if (!ft_strncmp(tokens.next_token->data , "-n",2))
        {
            tokens = tokens.next_token->next_token;
            if (tokens == NULL )
                return;
            ft_print(data);
        }
        else 
        {
            tokens = tokens.next_token;
            ft_print(data);
            write(1, "\n",1 );
        }
    }
}

                        