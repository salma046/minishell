#include "minishell.h"

t_minishell	g_minishell;


int	prepar_for_execution(t_minishell data)
{
	// if (mksome_files(data.count_pips, data) < 0)
	// 	return (-2);
	if (assign_files(data, data.nodes) < 0)
		return (-1);
	if (ft_check_redirections(data.nodes) < 0) // just open files fhad lmrhala and do nothing.;
		return (-1);
	return (0);
}

int main3(t_minishell data)
{
    t_token *temp_tokens;
	t_node 	*temp_nodes;

	temp_nodes = data.nodes;
	data.count_pips = count_pipe(temp_nodes);
    temp_tokens = data.tokens;
	prepar_for_execution(data);
	while(temp_nodes)
	{
		// printf("hello worlddddd\n");
		// printf("the cmd[0] is  : %s\n", temp_nodes->cmd[0]);
		if (temp_nodes->cmd[0] == NULL)
		{
			temp_nodes = temp_nodes->next_node;
			continue ;
		}
		if (ft_check_builtins(temp_nodes->cmd[0]) == 1)
			check_command(data, temp_nodes);
		else
		{
			// printf("the cmd[0] is not a buil: %s\n", data.nodes->cmd[0]);
			data.envirement = mk_tenv_char(data.envir);
			printf("hi cmd-------:%s\n", temp_nodes->cmd[0]);
			int retu = ft_execute(data, temp_nodes, data.envirement);
			if (retu == 127)
			{
				free_env_array(data.envirement);
				return 1;
			}
			free_env_array(data.envirement);
		}
		temp_nodes = temp_nodes->next_node;
	}
	// free_fds(data);
    return (0);

}

void handle_sigint(int sig)
{
	(void)sig;
	printf("\n\033[1;35m Minishell~$ \033[0m");
}

int	main(int ac, char *av[], char **env)
{
	signal(SIGINT, handle_sigint);
	if (ac > 2)
		return (1);
	(void)av;
	g_minishell.envirement = env;
	g_minishell.envir = mk_env(g_minishell.envirement);
	g_minishell.export_env = mk_env_4expo(g_minishell.envirement);

	while (1)
	{
		g_minishell.command = readline("\033[1;35m Minishell~$ \033[0m");
		if (!g_minishell.command)
		{
			printf("exit!\n");
			free_env_list(g_minishell.envir);
			free_env_list(g_minishell.export_env);
			free(g_minishell.command);
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
		g_minishell.nodes = mk_nodes(g_minishell.tokens);
		g_minishell.count_pips = count_pipe(g_minishell.nodes);
		g_minishell.files = mksome_files(g_minishell.count_pips);
		main3(g_minishell);
		free_node_list(g_minishell.nodes);
	}
}