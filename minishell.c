#include "minishell.h"

t_minishell	g_minishell;

void	free_env_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
int	ft_check_to_execute(t_token *temp_tokens, char **env)
{
	int	retu;

	retu = ft_execute(temp_tokens, env);
	if (retu == 127)
	{
		free_env_array(env);
		return (1);
	}
	free_env_array(env);
	return (0);
}

int	main3(t_minishell data)
{
	t_token	*temp_tokens;

	temp_tokens = data.tokens;
	if (ft_check_building(temp_tokens))
	{
		if (!ft_strcmp(temp_tokens->data, "env") && temp_tokens->data)
			ft_env(data);
		if (!ft_strcmp(temp_tokens->data, "unset") && temp_tokens->data)
			ft_unset(NULL, data);
		check_command(temp_tokens, data.export_env, data.envir);
	}
	else
	{
		data.envirement = mk_tenv_char(data.envir);
		ft_check_to_execute(temp_tokens, data.envirement);
	}
	printf("\033[36m-->out:%s\033[0m\n", temp_tokens->data);
	return (0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n\033[1;35m Minishell~$ \033[0m");
}
int	has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->data_type == PIPE)
		{
			return (1);
		}
		tokens = tokens->next_token;
	}
	return (0);
}
// void	ft_checkk(t_node *tmp_node)
// {
// 	t_node	*tmp;

// 	tmp = tmp_node;
// 	int i, j;
// 	while (tmp)
// 	{
// 		j = 0;
// 		i = 0;
// 		printf("----------------------------------------------------------\n");
// 		while (tmp->cmd[j])
// 		{
// 			printf("the node \033[32m%d\033[0m cmds n* %d is :\033[32m
// 				%s\033[0m\n", i, j, tmp->cmd[j]);
// 			j++;
// 		}
// 		tmp = tmp->next_node;
// 	}
// }

int	main(int ac, char *av[], char **env)
{
	t_node *tmp_node; // SOJod
	// int i = 0, j = 0;
	signal(SIGINT, handle_sigint);
	if (ac > 2)
		return (1);
	(void)av;
	g_minishell.envirement = env;
	g_minishell.in_file = open("/tmp/in_file", O_WRONLY | O_CREAT | O_APPEND,
			0644);
	g_minishell.out_file = open("/tmp/out_file", O_WRONLY | O_CREAT | O_APPEND,
			0644);
	g_minishell.envir = mk_env(g_minishell.envirement);
	g_minishell.export_env = mk_env_4expo(g_minishell.envirement);

	while (1)
	{
		g_minishell.command = readline("\033[1;35m Minishell~$ \033[0m");
		if (!g_minishell.command)
		{
			printf("Quiting minishell!\n");
			free_env_list(g_minishell.envir);
			free_env_list(g_minishell.export_env);
			clear_history();
			exit(1);
		}
		add_history(g_minishell.command);
		g_minishell.tokens = ft_tokenize(g_minishell);
		free(g_minishell.command);
		if (!g_minishell.tokens)
			continue ;
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		if (main_heredoc(g_minishell.tokens) < 0)
			continue ;
		if (ft_check_redirections(&g_minishell, g_minishell.tokens) < 0)
			continue ;

		// if (has_pipe(g_minishell.tokens))
		// {
		// 	printf("Pipe detected in command!\n");
		// 	// if(execute_piped_commands(tmp_node, env) == -1)
		// 	// {
		// 	// 	perror("pipe__execution");
		// 	// 	return (1);
		// 	// }
		// 	continue ;
		// }
		// else

		// main3(g_minishell);

		g_minishell.nodes = mk_nodes(g_minishell.tokens);
		tmp_node = g_minishell.nodes;
		if (has_pipe(g_minishell.tokens))
		{
			printf("Pipe detected in command!\n");
			if (execute_piped_commands(tmp_node, env) == -1)
			{
				perror("pipe__execution");
				return (1);
			}
			continue ;
		}
		else
			// {
			main3(g_minishell);
		// continue ;
		// }
		// else
		// ft_checkk(tmp_node);
		// while (tmp_node)
		// {
		// 	j = 0;
		// 	i = 0;
		// 	printf("----------------------------------------------------------\n");
		// 	while(tmp_node->cmd[j])
		// 	{
		// 		printf("the node \033[32m%d\033[0m cmds n* %d is :\033[32m
					// %s\033[0m\n",
		// 		i, j, tmp_node->cmd[j]);
		// 		j++;
		// 	}

		// 	while(tmp_node->redir)
		// 	{
		// 		printf("the redir file name is: %s\n",
		// 			tmp_node->redir->file);
		// 		printf("the redir type is: %d\n",
		// 			tmp_node->redir->red_type);
		// 		tmp_node->redir = tmp_node->redir->next;
		// 	}
		//  	printf("----------------------------------------------------------\n");
		// 	tmp_node = tmp_node->next_node;
		// 	i++;
		// }
		// free_node_list(g_minishell.nodes);
	}
}