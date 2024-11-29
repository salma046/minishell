#include "../minishell.h"

void	check_command(t_token *data, t_env *expo_envir, t_env *env_envir)
{
	t_token	*temp_tokens;
	temp_tokens = data;
	printf("c\n");
	if (!ft_strcmp(temp_tokens->data, "echo") && temp_tokens->data)
		ft_echo(temp_tokens);
	if (!ft_strcmp(temp_tokens->data, "cd") && temp_tokens->data)
		ft_cd(temp_tokens);
	if (!ft_strcmp(temp_tokens->data, "pwd") && temp_tokens->data)
		ft_pwd(temp_tokens);
	if (!ft_strcmp(temp_tokens->data, "exit") && temp_tokens->data)
		ft_exit(temp_tokens);
	// if (!ft_strcmp(temp_tokens->data, "export") && temp_tokens->data)
		// ft_export(temp_tokens,  env);
	if (!ft_strcmp(temp_tokens->data, "export") && temp_tokens->data)
		ft_export(temp_tokens, expo_envir, env_envir);
}
