#include "../minishell.h"

// void	ft_pwd(t_node *node)
// {
// 	char *pwd = getcwd(NULL, 0);
// 	if (pwd)
// 	{
// 		write(node->out_file, pwd, ft_strlen(pwd));
// 		write(node->out_file, "\n", 1);
// 		free(pwd); 
// 	}
// 	else
// 		perror("PWD");

// }


void	ft_pwd(t_node *data)
{
	 char *pwd = getcwd(NULL, 0);
	(void)data;
	printf("          \033[0;31m--> ANA f pwd  <-- \033[0m\n<-- ");
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("NOT");
}
