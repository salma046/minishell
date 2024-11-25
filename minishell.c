#include "minishell.h"

t_minishell	g_minishell;


int main3(t_minishell data, t_env *envir, char **env)
{
	t_token	*temp_tokens;

	temp_tokens = data.tokens;
	
	while (temp_tokens)
	{
		if (!ft_strcmp(temp_tokens->data, "env") && temp_tokens->data)
			ft_env(data);
		if (!ft_strcmp(temp_tokens->data , "unset") && temp_tokens->data)
			ft_unset(NULL,  data);
		check_command(temp_tokens, envir, env);
		// ft_execute(&data);
		temp_tokens = temp_tokens->next_token;
	}
	return (0);
}

int	main(int ac, char *av[], char **env)
{
	// t_node	*tmp_node;
	// int		i;
	// int		j;

	if (ac > 2) // Sojod
		return (1);
	(void)av;
	g_minishell.envirement = env;
	g_minishell.envir = mk_env(g_minishell.envirement);
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
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		if (main_heredoc(g_minishell.tokens) < 0)
			continue ;
		if (ft_check_redirections(&g_minishell, g_minishell.tokens) < 0)
			continue ;
		// if (unlink("/tmp/heredoc.txt") == -1)
		// 	dprintf(2, "error deleting the file\n");

		main3(g_minishell, g_minishell.envir, env); //execution starts here;;;;
		g_minishell.nodes = mk_nodes(g_minishell.tokens); ///// This function just took me somuch time and now there is a possibility it won't be used at all ooof
		// tmp_node = g_minishell.nodes;
		// while (tmp_node)
		// {
		// 	j = 0;
		// 	i = 0;
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
		// 	tmp_node = tmp_node->next_node;
		// 	i++;
		// }
		free_node_list(g_minishell.nodes);
	}
}
