#include "../minishell.h"

int	ft_check_building(t_token *token)
{
	if (!token || !token->data)
		return (0);
	if (!ft_strcmp(token->data, "echo"))
		return (1);
	if (!ft_strcmp(token->data, "cd"))
		return (1);
	if (!ft_strcmp(token->data, "pwd"))
		return (1);
	if (!ft_strcmp(token->data, "exit"))
		return (1);
	if (!ft_strcmp(token->data, "export"))
		return (1);
	if (!ft_strcmp(token->data, "unset"))
		return (1);
	if (!ft_strcmp(token->data, "env"))
		return (1);
	return (0);
}
void	check_command(t_token *data, t_env *expo_envir, t_env *env_envir)
{
	t_token	*temp_tokens;

	temp_tokens = data;
	if (!ft_strcmp(temp_tokens->data, "echo") && temp_tokens->data)
		ft_echo(temp_tokens);
	if (!ft_strcmp(temp_tokens->data, "cd") && temp_tokens->data)
		ft_cd(temp_tokens);
	if (!ft_strcmp(temp_tokens->data, "pwd") && temp_tokens->data)
		ft_pwd(temp_tokens);
	if (!ft_strcmp(temp_tokens->data, "exit") && temp_tokens->data)
		ft_exit(temp_tokens);
	if (!ft_strcmp(temp_tokens->data, "export") && temp_tokens->data)
		ft_export(temp_tokens, expo_envir, env_envir);
}
