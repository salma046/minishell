#include "../minishell.h"
// export alone
void	sort_env(t_env *envir)
{
    printf("aaa");
	t_env	*new_env;
	char	*tmp_key;
	char	*tmp_value;

	if (envir == NULL || envir->next == NULL)
		return ;
    (void)envir;
	new_env = envir->next;
	while (new_env)
	{
		if (ft_strcmp(envir->key, new_env->key) > 0)
		{
			tmp_key = envir->key;
			envir->key = new_env->key;
			new_env->key = tmp_key;
			tmp_value = envir->value;
			envir->value = new_env->value;
			new_env->value = tmp_value;
		}
		new_env = new_env->next;
	}
	sort_env(envir->next);
}
void	ft_env_export_once(t_token *data, t_env *envir, int active)
{
	(void)data;
	t_env	*head;
	t_env	*current;

	head = envir;

	if (active == 1)
		sort_env(head);
	current = head;

	while (current)
	{
		if (active == 1)
			printf("declare -x %s=%s\n", current->key, current->value);
		current = current->next;
	}
}
// export alone

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


int ft_check(t_env *envir, char *key, char *value)
{
    size_t key_len;
	t_env *tmp_env;
    
	tmp_env = envir;
    key_len = ft_strlen(key);
    if (!envir || !key || !value)
        return 0;
    
    while (tmp_env)
    {
        if (ft_strncmp(tmp_env->key, key, key_len) == 0 && tmp_env->key[key_len] == '=')
        {
            free(tmp_env->key);
            size_t new_len = key_len + ft_strlen(value) + 2;  
            tmp_env->key = malloc(new_len);
            if (!tmp_env->key)
            {
                perror("malloc");
                return -1;  
            }
            
            ft_strlcpy(tmp_env->key, key, new_len);
            ft_strlcat(&tmp_env->equal, "=", new_len);
            ft_strlcat(tmp_env->value, value, new_len);
            return 1;  
        }
        tmp_env = tmp_env->next;
    }
    
    return 0; 
}


// void	ft_adding_in_export_once(t_env *head, int active)
// {
// 	// printf("\033[36mthis is the head->key: %s\033[0m\n", head->key);
// 	// printf("\033[36mthis is the head->value: %s\033[0m\n", head->value);
// 	// printf("\033[36mthis is the active: %d\033[0m", active);
// 	t_env *current = head;

// 	while (current) 
// 	{
// 		if (current->value)
// 			printf("declare -x %s=\"%s\"\n", current->key, current->value);
// 		else if (active == 1 || active == 0)
// 			printf("\033[1;35mdeclare -x %s\033[0m\n", current->key);
// 		current = current->next;
// 	}
// }

void key_without_equal(t_token *data, t_env *envir, int active) {
    t_env *last_node = envir;
	t_token *temp_tokens = data;
    (void)active;

    // Find the last node of the existing envir list
    while (last_node && last_node->next != NULL) {
        last_node = last_node->next;
    }

    // Process the tokens and add new t_env nodes
    while (temp_tokens && temp_tokens->next_token) {
        t_env *new_export = (t_env *)malloc(sizeof(t_env));
        if (!new_export)
            exit(1);

        // Allocate and copy the key
        new_export->key = ft_strdup(temp_tokens->next_token->data);
        new_export->value = NULL; // Set value to NULL as per your logic
        new_export->next = NULL; // Initialize next to NULL

        // Append the new node to the list
        if (last_node == NULL) {
            // If envir is empty, this becomes the first node
            envir = new_export;
        } else {
            last_node->next = new_export; // Attach to the end of the list
        }
        last_node = new_export; // Update the last_node pointer

        temp_tokens = temp_tokens->next_token; // Move to the next token
    }
}

 
void ft_add_to_export_arg(t_token *tokens, t_env *envir)
{
    t_token *current_token;
    t_env   *expo;
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
        
        expo = malloc(sizeof(t_env));
        if (!expo)
        {
            perror("malloc");
            return;
        }
        
        splitVar = ft_strchr(token_data, '=');
        if (!splitVar)
        {
           key_without_equal(tokens, envir, 0);
		   t_env *hi = envir;
		   while (hi)
		   {
				printf("the key is: %s\n", hi->key);
				hi = hi->next;
		   }
        //    printf("%s", splitVar);
            free(expo);
            current_token = current_token->next_token;
            continue;
        }
		// t_env *hello = envir;
		// while(hello)
        printf("\033[1;35mthis is expo: %s\033[0m", splitVar);
        expo->key = ft_strndup(token_data, splitVar - token_data);
        expo->value = ft_strdup(splitVar + 1);
        
        if (!expo->key || !expo->value)
        {
            free(expo->key);
            free(expo->value);
            free(expo);
            current_token = current_token->next_token;
            continue;
        }
        
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
        
        free(expo->key);
        free(expo->value);
        free(expo);
        
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
        ft_env_export_once(tokens, envir, active);
    }
    else
    {
        active = 0;
        // ft_add_to_export_arg(tokens, envir);
        // ft_env_export_once(tokens, envir, active);
		printf("\n---2---\n");
    }
    return ;
}