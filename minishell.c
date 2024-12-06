#include "minishell.h"

t_minishell	g_minishell;

int	ft_open_red_files(t_minishell data)
{
	if (ft_check_redirections(data.nodes) < 0)
		return (-1);
	return (0);
}
void	child_process(t_node *nodes, t_minishell data, int pipe_fd[2], int *in_fd)
{
	char	*command_path;

	if (nodes->redir && ft_check_redirections(nodes) == -1)
		exit(EXIT_FAILURE);
	dup2(*in_fd, STDIN_FILENO); // Redirect input.
	// Handle output redirection.
	if (nodes->next_node)
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirect output to pipe.
	// Handle output redirection to file if specified.
	if (nodes->redir && ft_check_redirections(nodes) == 0)
	{
		if (nodes->redir->red_type == OUT_REDIR
			|| nodes->redir->red_type == APPEND)
		{
			// Redirect to file.
			dup2(nodes->out_file, STDOUT_FILENO);
		}
		if (nodes->redir->red_type == INP_REDIR)
		{
			// Redirect input from file.
			dup2(nodes->in_file, STDIN_FILENO);
		}
	}
	dup2(*in_fd, STDIN_FILENO);
	if (nodes->next_node)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]); // Close unused read end in the child.
	close(pipe_fd[1]);
	if (ft_check_builtins(nodes->cmd[0]) == 1)
	{
		check_command(&data, nodes);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("hi from not builtins!!!\n");
		command_path = find_command_path(nodes->cmd[0], data.envirement);
		if (!command_path)
		{
			fprintf(stderr, "%s: command not found\n", nodes->cmd[0]);
			exit(127);
		}
		execve(command_path, nodes->cmd, data.envirement);
		perror("execve");
		exit(127);
	}
}

void execute_single_command()
{

}

int	main3(t_minishell data)
{
	t_node	*temp_nodes;
	int		pipe_fd[2];
	int		in_fd;
	pid_t	pid;

	temp_nodes = data.nodes;
    if (data.nodes->next_node == NULL)
    {
		// check if the command is a builtin and execute it WITHOUT FORKING!!!!!!!
		// envirement
        hadi_one(data.tokens, data.envirement);
		return 0;
    }
    // printf("this is the env:%s", data.envirement[0]);
	// if (prepar_for_execution(data))
	while (temp_nodes)
	{
		// if (temp_nodes->cmd[0] == NULL)
		// {
		//     temp_nodes = temp_nodes->next_node;
		//     continue ;
		// }
		if (temp_nodes->next_node)
			pipe(pipe_fd); // check on the pipes
		pid = fork();      // check on the forks
		if (pid == 0)      // Child process
            child_process(temp_nodes, data, pipe_fd, &in_fd);
		else // Parent process
		{
			waitpid(pid, NULL, 0);
			if (temp_nodes->next_node)
			{
				close(pipe_fd[1]);
				in_fd = pipe_fd[0];
			}
		}
		temp_nodes = temp_nodes->next_node;
	}
	return (0);
}

int	main(int ac, char *av[], char **env)
{
	signal(SIGINT, handle_sigint);
	if (ac >= 2)
		return (1);
	(void)av;
	g_minishell.envirement = env;
	g_minishell.envir = mk_env(g_minishell.envirement);
	g_minishell.export_env = mk_env_4expo(g_minishell.envirement);
	while (1)
	{
		g_minishell.command = readline("Minishell~$ ");
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
		// g_minishell.files = mksome_files(g_minishell.count_pips);
		main3(g_minishell);
		free_node_list(g_minishell.nodes);
	}
}
