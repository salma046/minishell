#include "minishell.h"

void check_command(t_minishell data)
{
	if (!ft_strncmp(data.tokens->data , "echo", 4) && data.tokens->data)
    	ft_echo(data);
	if (!ft_strncmp(data.tokens->data , "cd", 2) && data.tokens->data)
		ft_cd(data);
	if (!ft_strncmp(data.tokens->data , "pwd", 3) && data.tokens->data)
		ft_pwd(data);
}