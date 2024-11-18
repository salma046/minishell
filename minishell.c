#include "minishell.h"

t_minishell	g_minishell;

void free_redir_list(t_redir *redir)
{
    t_redir *current;
    t_redir *next;

    current = redir;
    while (current != NULL)
    {
        next = current->next;
        free(current->file);
        free(current);
        current = next;
    }
}

void free_node(t_node *node)
{
    int i = 0;

    if (node->cmd)
    {
        while (node->cmd[i])
        {
            free(node->cmd[i]);
            i++;
        }
        free(node->cmd);
    }

    if (node->redir)
	{
        free_redir_list(node->redir);
	}
	free(node);
}

void free_node_list(t_node *node_list)
{
    t_node *current;
    t_node *next;

    current = node_list;
    while (current != NULL)
    {
        next = current->next_node;
        free_node(current);
        current = next;
    }
}

int main3(t_minishell data)
{
	t_token	*temp_tokens;

	temp_tokens = data.tokens;
	while (temp_tokens)
	{
		if (!ft_strcmp(data.tokens->data , "env") && data.tokens->data)
			ft_env(data);
		if (!ft_strcmp(data.tokens->data , "unset") && data.tokens->data)
			ft_unset(NULL,  data);
		check_command(temp_tokens);
		// ft_execute(&data);
		temp_tokens = temp_tokens->next_token;
	}
	return (0);
}

int	main(int ac, char *av[], char **env)
{
	if (ac > 2) // Sojod
		return (1);
	(void)av;
	g_minishell.envirement = env;
	t_node *tmp_node;
	int i;
	int j;

	while (1)
	{
		g_minishell.command = readline("Minishell~$ ");
		if (!g_minishell.command)
		{
			printf("Quiting minishell!\n");
			// free structs
			exit(1);
		}
		add_history(g_minishell.command);
		g_minishell.tokens = ft_tokenize(g_minishell);
		if (!g_minishell.tokens)
			continue ;
		// g_minishell.tokens = rmp_dollar(g_minishell.tokens);
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		if (main_heredoc(g_minishell.tokens) < 0)
			continue;
		// if (ft_output(g_minishell.tokens) < 0)  // sojod
        // 	continue;
        
   		if (ft_input(g_minishell.tokens) < 0)  //sojod
        	continue;
		// if (unlink("/tmp/heredoc.txt") == -1)
		// 	dprintf(2, "error deleting the file\n");
		main3(g_minishell); //execution starts here;;;;
		g_minishell.nodes = mk_nodes(g_minishell.tokens); ///// This function just took me somuch time and now there is a possibility it won't be used at all ooof
		tmp_node = g_minishell.nodes;
		while (tmp_node)
		{
			j = 0;
			i = 0;
			// printf("----------------------------------------------------------\n");
			// while(tmp_node->cmd[j])
			// {
			// 	printf("the node \033[32m%d\033[0m cmds n* %d is :\033[32m %s\033[0m\n",
			// 	i, j, tmp_node->cmd[j]);
			// 	j++;
			// }
			// while(tmp_node->redir)
			// {
			// 	printf("the redir file name is: %s\n",
			// 		tmp_node->redir->file);
			// 	printf("the redir type is: %d\n",
			// 		tmp_node->redir->red_type);
			// 	tmp_node->redir = tmp_node->redir->next;
			// }
			// printf("----------------------------------------------------------\n");
			tmp_node = tmp_node->next_node;
			i++;
		}
		free_node_list(g_minishell.nodes);
	}
}
