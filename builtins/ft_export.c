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


// int ft_check(t_env *envir, char *key, char *value)
// {
//     size_t key_len;
// 	t_env *tmp_env;
    
// 	tmp_env = envir;
//     key_len = ft_strlen(key);
//     if (!envir || !key || !value)
//         return 0;
    
//     while (tmp_env)
//     {
//         if (ft_strncmp(tmp_env->key, key, key_len) == 0 && tmp_env->key[key_len] == '=')
//         {
//             free(tmp_env->key);
//             size_t new_len = key_len + ft_strlen(value) + 2;  
//             tmp_env->key = malloc(new_len);
//             if (!tmp_env->key)
//             {
//                 perror("malloc");
//                 return -1;  
//             }
            
//             ft_strlcpy(tmp_env->key, key, new_len);
//             ft_strlcat(&tmp_env->equal, "=", new_len);
//             ft_strlcat(tmp_env->value, value, new_len);
//             return 1;  
//         }
//         tmp_env = tmp_env->next;
//     }
    
//     return 0; 
// }

//  3 steps if there is a value to the export key
//1: check if it is already on the lest ==> delete it
//2: check if after the "=" sign there is a word;
//3: if no word found;

void key_with_equal(t_token *tokens, t_env *envir) {
	
	t_env *head = NULL;
	t_token *temp_tokens;
    int a;
	

	temp_tokens = tokens;
	head = envir;
    a = check_key("d", envir);
    printf("the current token is: %s\n", tokens->data);
    
	while (head && head->next != NULL) {
        head = head->next;
    }
	while (temp_tokens && check_key(temp_tokens->data, envir) == 0)
	{
	    t_env *new_export = (t_env *)malloc(sizeof(t_env));
	    if (!new_export)
	        exit(1);

	    new_export->key = ft_strdup(temp_tokens->data);
	    // new_export->value = ;
	    new_export->next = NULL;

	    if (head == NULL)
	        envir = new_export;
	    else
	        head->next = new_export;
	    head = new_export;

	    temp_tokens = temp_tokens->next_token; 
	}
}
 
void ft_add_to_export_arg(t_token *tokens, t_env *envir)
{
    t_token *current_token;
    char    *token_data;
    char    *splitVar;
    // size_t  len;
    // char    *new_env_str;
    int     i;
    
    if (!tokens || !tokens->next_token || !envir)
        return;
    current_token = tokens->next_token;
    while (current_token != NULL)
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
        {
            printf("hellllo world\n");
            key_without_equal(current_token, envir, 0);
            current_token = current_token->next_token;
            continue;
        }
        else
        {
            t_env *expo;
            // printf("\033[1;35mthis is expo: %s\033[0m", splitVar);
            expo->key = ft_strndup(token_data, splitVar - token_data);
            expo->value = ft_strdup(splitVar + 1);
            printf("the key is: %s\nthe value is: %s\n", expo->key, expo->value);
        }
        // else
        // {
        //     printf("not helllo woorld\n");
        //     key_with_equal(current_token, envir);
        // }
        // int check_result = ft_check(envir, expo->key, expo->value);
        
        // if (check_result == 0)
        // {
		// 	t_env *tmp_env = envir;
        //     i = 0;
        //     while (tmp_env != NULL)
        //         tmp_env = tmp_env->next;
            
        //     len = ft_strlen(expo->key) + ft_strlen(expo->value) + 2;
        //     new_env_str = malloc(len);
        //     if (!new_env_str)
        //     {
        //         free(expo->key);
        //         free(expo->value);
        //         free(expo);
        //         current_token = current_token->next_token;
        //         continue;
        //     }
            
        //     ft_strlcpy(new_env_str, expo->key, len);
        //     ft_strlcat(new_env_str, "=", len);
        //     ft_strlcat(new_env_str, expo->value, len);
            
        //     envir[i] = new_env_str;
        //     envir[i + 1] = NULL;
        // }

        current_token = current_token->next_token;
    }
}

void    ft_export(t_token *tokens, t_env *envir)  
{
    int active = 0;
	
    if (!tokens || !envir) 
        return;
	
    active = 1;
    if ((tokens->next_token == NULL && tokens->data)) 
    {
		if (tokens->prev_token && !ft_strcmp(tokens->prev_token->data, "export"))
			return ;
        ft_env_export_once(tokens, envir, active);
    }
    else
    {
        active = 0;
        ft_add_to_export_arg(tokens, envir);
        // ft_env_export_once(tokens, envir, active);
		printf("\n---2---\n");
    }
    
}
