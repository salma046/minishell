#include "../minishell.h"

int		check_key(char *str, t_env *envir)
{
	t_env *temp_env;

	temp_env = envir;

	while (temp_env)
	{
		if (!ft_strcmp(temp_env->key, str))
			return (1);
		temp_env = temp_env->next;
	}
	return (0);
}
void key_without_equal(t_token *tokens, t_env *envir, int active) {
	
	t_env *head = NULL;
	t_token *temp_tokens;
	

	temp_tokens = tokens;
	head = envir;
    (void)active;


	while (head && head->next != NULL) {
        head = head->next;
    }
	while (temp_tokens && check_key(temp_tokens->data, envir) == 0)
	{
	    t_env *new_export = (t_env *)malloc(sizeof(t_env));
	    if (!new_export)
	        exit(1);

	    new_export->key = ft_strdup(temp_tokens->data);
	    new_export->value = NULL;
	    new_export->next = NULL;

	    if (head == NULL)
	        envir = new_export;
	    else
	        head->next = new_export;
	    head = new_export;

	    temp_tokens = temp_tokens->next_token; 
	}
}


// export alone

void	sort_env(t_env *envir)
{
	t_env	*new_env;
	char	*tmp_key;
	char	*tmp_value;

	if (envir == NULL || envir->next == NULL)
		return ;
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
        if (current->value == NULL || !ft_strcmp(current->value, ""))
        {
            current->value = ft_strdup("");
			printf("declare -x %s%s\n", current->key, current->value);
        }
		else if (active == 1)
			printf("declare -x %s=%s\n", current->key, current->value);
		current = current->next;
	}
}
// export alone

