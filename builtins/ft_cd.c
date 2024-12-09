#include "../minishell.h"

// int	ft_cd(t_minishell *data)
// {
// 	// t_token	*tmp_node;
// 	t_node *node;
// 	node  = data->nodes;
// 	int i = 0;
// 	while(node)
// 	{
// 		printf("%s", node->cmd[i]);
// 		i++;
// 		// node = node->next_node;
// 	// }
	// tmp_tokens = data->tokens;
	// while (tmp_tokens)
	// {
	// 	if (!ft_strcmp(tmp_tokens->data, "cd")
	// 		&& tmp_tokens->next_token == NULL)
	// 	{
	// 		if (chdir(getenv("HOME")) == -1)
	// 			perror("cd");
	// 		printf("Home path:  \033[0;31m%s\033[0m\n", getenv("HOME"));
	// 	}
	// 	if (!ft_strcmp(tmp_tokens->data, "cd") && tmp_tokens->data)
	// 	{
	// 		printf("This is the path of cd:%s\n", getenv("HOME"));
	// 		if (tmp_tokens->next_token && chdir(tmp_tokens->next_token->data)
	// 			== -1)
	// 			perror("\033[32m ERROR\033[0m");
	// 		else
	// 			printf("DONE ✅\n");
	// 	}
	// 	tmp_tokens = tmp_tokens->next_token;
	// }
	// return (0);
// }
int ft_cd(t_minishell *data)
{
    t_node *tmp_node = data->nodes; 
    int i = 0;

    while (tmp_node) 
    {
        i = 0; 
        while (tmp_node->cmd && tmp_node->cmd[i]) 
        {
            if (!ft_strcmp(tmp_node->cmd[i], "cd"))
            {
                if (!tmp_node->cmd[i + 1]) 
                {
                    char *home_path = getenv("HOME");
                    if (!home_path)
                    {
                        write(tmp_node->out_file, "cd: HOME not set\n", 17);
                        return (1);
                    }
                    if (chdir(home_path) == -1)
                    {
                        perror("cd");
                        return (1);
                    }
                    printf("Changed to HOME: %s\n", home_path);
                }
                else 
                {
                    if (chdir(tmp_node->cmd[i + 1]) == -1)
                    {
                        perror("cd");
                        return (1);
                    }
                    printf("Changed to: %s\n", tmp_node->cmd[i + 1]);
					// printf("%d")
                }
                return (0); 
            }
            i++;
        }
        tmp_node = tmp_node->next_node;
    }
    return (0);
}





