#include "../minishell.h"

int is_special_char(char c)
{
        return (c >= 33 && c <= 47) ||  
           (c >= 58 && c <= 64) ||  
           (c >= 91 && c <= 96) ||  
           (c >= 123 && c <= 126);}

int has_doubled_special_chars(char *token)
{
    if (!token)
        return 0;

    int i = 0;
    while (token[i] != '\0' && token[i] != '=')
    {
        if (token[i + 1] != '\0' && 
            is_special_char(token[i]) && 
            is_special_char(token[i + 1]))
        {
            return 1;  
        }
        i++;
    }
    return 0;  
}

//  3 steps if there is a value to the export key
//1: check if it is already on the lest ==> delete it
//2: check if after the "=" sign there is a word;
//3: if no word found;

char    *put_quot2_value(char *str)
{
    char    *result;
    int     i;
    int     j;

    i = 0;
    j = 0;
    result = malloc(sizeof(char) * ft_strlen(str) + 3);
    if (!result)
        return NULL;
    result[j++] = '"';
    while (str[i])
        result[j++] = str[i++];
    result[j] = '"';
    result[++j] = '\0';
    free(str);
    return (result);
}

void key_with_equal(t_token *tokens, t_env *envir)
{
	t_env   *head = NULL;
	t_token *temp_tokens;
    t_env   *new_export;
    char    *splitVar;

	head = envir;
	while (head && head->next != NULL) {
        head = head->next;
    }
	temp_tokens = tokens;
    splitVar = ft_strchr(temp_tokens->data, '=');
    new_export = malloc(sizeof(t_env));
    if (!new_export) {
        perror("malloc");
        return ;
    }
    if (!splitVar) {
        printf("Error: '=' not found in token_data.\n");
        free(new_export);
        return ;
    }
    new_export->key = ft_strndup(temp_tokens->data, splitVar - temp_tokens->data);
    new_export->value = put_quot2_value(ft_strdup(splitVar + 1));
    new_export->equal = '=';
	new_export->next = NULL;
    // if (check_key(new_export->key, envir) == 1)
    // {
    //     removeNode(&envir, new_export->key);
    // }
	if (head == NULL)
	    envir = new_export;
	else
	    head->next = new_export;
	head = new_export;
}
 
void ft_add_to_export_arg(t_token *tokens, t_env *envir)
{
    t_token *current_token;
    char    *token_data;
    char    *splitVar;
    int     i;
    
    if (!tokens || !tokens->next_token || !envir)
        return;
    current_token = tokens->next_token;
    while (current_token != NULL && current_token->data_type == WORD)
    {
        token_data = current_token->data;
        if (!token_data)
        {
            current_token = current_token->next_token;
            continue;
        }
        
        if (ft_strcmp(token_data, "=") == 0 ||
            token_data[0] == '=' ||
            ft_isdigit(token_data[0]) ||
            is_special_char(token_data[0]) ||
            has_doubled_special_chars(token_data))
        {
            printf("bash: export: %s': not a valid identifier\n", token_data);
            current_token = current_token->next_token;
            continue;
        }

        i = 0;
        while (token_data[i] != '\0' && token_data[i] != '=')
        {
            if (is_special_char(token_data[i]))
            {
                printf("bash: export: %s': not a valid identifier\n", token_data);
                current_token = current_token->next_token;
                break;
            }
            i++;
        }

        if (token_data[i] != '\0' && token_data[i] != '=')
            continue;
        splitVar = ft_strchr(token_data, '=');
        if (!splitVar)
            key_without_equal(current_token, envir, 0);
        else
        {
            if (check_key( ft_strndup(current_token->data, splitVar - current_token->data), envir) == 1)
            {
                removeNode(&envir, ft_strndup(current_token->data, splitVar - current_token->data));
            }
            key_with_equal(current_token, envir);
        }
        current_token = current_token->next_token;
    }
}

char    *rm_quot2_value(char *str)
{
    char    *result;
    int     i;
    int     j;

    i = 1;
    j = 0;
    if (!ft_strcmp(str, ""))
    {
        free(str);
        return (ft_strdup(""));
    }
    result = malloc(sizeof(char) * ft_strlen(str) - 1);
    if (!result)
        return NULL;
    while (str[i + 1])
    {
        result[j++] = str[i++];
    }
    result[j] = '\0';
    free(str);
    return (result);
}

void    add_struc_2_env(t_env *new_env, t_env *head)
{
	t_env *new_head = NULL;
    new_head = head;

	while (new_head && new_head->next != NULL) {
        new_head = new_head->next;
    }
    new_env->value = rm_quot2_value(new_env->value);
    if (new_head == NULL)
	        head = new_env;
	    else
	        new_head->next = new_env;
	    new_head = new_env;
}

void    search_check_add_env(t_env *expo_envir, t_env *env_envir)
{
    t_env *to_check;

    to_check = expo_envir;
    while (to_check)
    {
        if (check_key(to_check->key, env_envir) != 1)
        {
            add_struc_2_env(to_check, env_envir);
        }
        to_check = to_check->next;
    }
    
}

void    ft_export(t_token *tokens, t_env *expo_envir, t_env *env_envir)  
{
    int active = 0;

    (void) env_envir;
    if (!tokens || !expo_envir) 
        return;
	
    active = 1;
    if ((tokens->next_token == NULL && tokens->data)) 
    {
		if (tokens->prev_token && !ft_strcmp(tokens->prev_token->data, "export"))
			return ;
        ft_env_export_once(tokens, expo_envir, active);
    }
    else
    {
        active = 0;
        ft_add_to_export_arg(tokens, expo_envir);
		printf("\n---2---\n");
    }
    // search_check_add_env(expo_envir, env_envir); ///// debugging all this function the concept seems to be correct
}
