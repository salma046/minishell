#include "../minishell.h"

void	ft_pwd(t_node *node)
{
	char *pwd = getcwd(NULL, 0);
	if (pwd)
	{
		write(node->out_file, pwd, ft_strlen(pwd));
		write(node->out_file, "\n", 1);
		free(pwd); 
	}
	else
		perror("PWD");

}


