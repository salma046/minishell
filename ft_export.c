#include "minishell.h"

void sort_env(t_senv *node)
{
   if (node == NULL || node->next == NULL)
    return ;
    t_senv *next_node = node->next;

    while (next_node)
    {
        if (ft_strcmp(node->skey, next_node->skey) > 0)
        {
            char  *tmp_key = node->skey;
            node->skey =  next_node->skey;
            next_node->skey = tmp_key;

            char  *tmp_value = node->svalue;
            node->svalue =  next_node->svalue;
            next_node->svalue = tmp_value;
        }
        next_node = next_node->next;
    }
    sort_env(node->next);
}

void ft_env_export_once(t_minishell data, int active)
{
    t_senv *head = NULL;
    t_senv *last_node = NULL;

    int i = 0;
    while (data.envirement[i] != NULL)
    {
        t_senv *cmd_env = (t_senv *)malloc(sizeof(t_senv));
        if (!cmd_env)
            exit(1);

        char *equal_env = strchr(data.envirement[i], '=');
        if (equal_env != NULL)
        {
            cmd_env->skey = strndup(data.envirement[i], equal_env - data.envirement[i]);
            cmd_env->svalue = strndup(equal_env + 1, strlen(data.envirement[i] + 1));
            cmd_env->sequal = '=';
            cmd_env->next = NULL;
        }

        if (last_node == NULL)
            head = cmd_env;
        else
            last_node->next = cmd_env;

        last_node = cmd_env;
        i++;
    }
    
    if (active == 1)
        sort_env(head);
    
    t_senv *current = head;
    while (current)
    {
        if (active == 1)
            printf("declare -x %s=%s\n", current->skey, current->svalue);
        current = current->next;
    }
}
void ft_add_to_export_arg(t_minishell data) 
{
    int i ;

    i = 0;
    t_env *expo = malloc(sizeof(t_env));
    if (!expo) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
   
    if (ft_isdigit(data.tokens->next_token->data[0]) ) {
        printf("bash: export: `%s': not a valid identifier\n", data.tokens->next_token->data);
        free(expo);
        return;
    }
    printf(" \033[1;35m data.tokens->next_token->data: %s \033[0m \n", data.tokens->next_token->data);

    char *token_data = data.tokens->next_token->data;

    while(data.tokens->next_token != NULL)
    {
        if (data.tokens->next_token->data[0] == '=')
        {
            printf("bash: export: `%s': not a valid identifier\n", data.tokens->next_token->data);
        }
        if (data.tokens->next_token == NULL)
            return ;
        printf(" ----> \033[0;31m %s \033[0m <---- \n", data.tokens->next_token->data);
       
        int k = 0;
     
         while (k < 5)
        {
            printf(" character: \033[32m %c \033[0m \n", data.tokens->next_token->data[k]);
            k++;
        }
        data.tokens->next_token = data.tokens->next_token->next_token;
    }
        
    char *splitVar = ft_strchr(token_data, '=');
    if (!splitVar)
        return ;

    expo->key = ft_strndup(token_data, splitVar - token_data);
    expo->value = ft_strndup(splitVar + 1, ft_strlen(splitVar + 1));

    i = 0;
    while (data.envirement[i] != NULL) {
        i++;
    }

    size_t len = ft_strlen(expo->key) + ft_strlen(expo->value) + 2;
    char *new_env_str = malloc(len);
    if (!new_env_str) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    ft_strlcpy(new_env_str, expo->key, ft_strlen(expo->key));
    ft_strcat(new_env_str, expo->value);
    
    data.envirement[i] = new_env_str;
    data.envirement[i + 1] = NULL; 
}

void ft_export(t_minishell data)
{
    int active = 1;

    if (data.tokens != NULL && data.tokens->next_token == NULL)
    {
        ft_env_export_once(data, active);
    }
    else
    {
        active = 0;
        ft_add_to_export_arg(data);
        ft_env_export_once(data, active);
    }
}
