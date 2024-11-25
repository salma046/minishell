#include "../minishell.h"

void	ft_pwd(t_token *data)
{
	char	pwd[PATH_MAX];

	(void)data;
	printf("            \033[0;31m--> ANA f pwd  <-- \033[0m\n<-- ");
	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("NOT");
}
