#include "minishell.h"

void check_command(t_minishell data)
{
	t_env *env_list =  NULL;
	if (!ft_strcmp(data.tokens->data , "echo") && data.tokens->data)
    	ft_echo(data);
	if (!ft_strcmp(data.tokens->data , "cd") && data.tokens->data)
		ft_cd(data);
	if (!ft_strcmp(data.tokens->data , "pwd") && data.tokens->data)
		ft_pwd(data);
	if (!ft_strcmp(data.tokens->data , "env") && data.tokens->data)
		ft_env(data);
	if (!ft_strcmp(data.tokens->data , "exit") && data.tokens->data)
		ft_exit(data);
	if (!ft_strcmp(data.tokens->data , "unset") && data.tokens->data)
		ft_unset(env_list,  data);
}