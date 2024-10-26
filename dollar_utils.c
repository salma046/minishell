#include "minishell.h"

int check_4_space(char *env_var)
{
    int i;

    i = 0;
    while (env_var[i])
    {
        if (env_var[i] == ' ' || env_var[i] == '\t' || env_var[i] == '\n' || env_var[i] == '\f')
            return (1);
        else
            i++;
    }
    return (0);
}

char	*new_token_env(t_token *tokens, char *env_var)
{
    t_token	*temp_tokens;
    t_token	*next_tokens;

	temp_tokens = tokens;
    next_tokens = tokens->next_token;

}
