#include "../minishell.h"

void check_command(t_token *data, char **env)
{
	t_token	*temp_tokens;

	temp_tokens = data;
	if (!ft_strcmp(temp_tokens->data , "echo") && temp_tokens->data)
    	ft_echo(temp_tokens);
	if (!ft_strcmp(temp_tokens->data , "cd") && temp_tokens->data)
		ft_cd(temp_tokens);
	if (!ft_strcmp(temp_tokens->data , "pwd") && temp_tokens->data)
		ft_pwd(temp_tokens);
	if (!ft_strcmp(temp_tokens->data , "exit") && temp_tokens->data)
		ft_exit(temp_tokens);
	//mine 
	// if (!ft_strcmp(data.tokens->data , "export") && data.tokens->data)
		// ft_export(data);
	// target
	if (!ft_strcmp(temp_tokens->data , "export") && temp_tokens->data)
		ft_export(temp_tokens, env);
}