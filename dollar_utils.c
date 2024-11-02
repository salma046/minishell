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

