#include "minishell.h"

void check_command(t_minishell data)
{
	t_env *env_list =  NULL;
	if (!ft_strncmp(data.tokens->data , "echo", 4) && data.tokens->data)
    	ft_echo(data);
	if (!ft_strncmp(data.tokens->data , "cd", 2) && data.tokens->data)
		ft_cd(data);
	if (!ft_strncmp(data.tokens->data , "pwd", 3) && data.tokens->data)
		ft_pwd(data);
	if (!ft_strncmp(data.tokens->data , "env", 3) && data.tokens->data)
		ft_env(data);
	if (!ft_strncmp(data.tokens->data , "exit", 4) && data.tokens->data)
		ft_exit(data);
	if (!ft_strncmp(data.tokens->data , "unset", 5) && data.tokens->data)
		ft_unset(env_list,  data);
}