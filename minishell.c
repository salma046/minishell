#include "minishell.h"

t_minishell	g_minishell;
int main3(t_minishell data) {
    t_node *temp_nodes = data.nodes;
    int pipe_fd[2] = {-1, -1};
    int in_fd = dup(STDIN_FILENO);
    pid_t pid;

    	// hadi rir dyal single command hitax radi i5sna nsipariwhoum 
    if (temp_nodes != NULL && temp_nodes->next_node == NULL) 
    {
        if (ft_check_builtins(temp_nodes->cmd[0]) == 1) 
        {
            if (check_command(&data, temp_nodes) == 1)
                printf("Executing built-in command: %s\n", temp_nodes->cmd[0]);
            return 0; 
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }
        if (pid == 0) {
            if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1)
                exit(EXIT_FAILURE);
            if (temp_nodes->redir && ft_check_redirections(temp_nodes) == 0) {
            }

            char *command_path = find_command_path(temp_nodes->cmd[0], data.envirement);
            if (!command_path) {
                printf("%s: command not found\n", temp_nodes->cmd[0]);
                exit(127);
            }
            execve(command_path, temp_nodes->cmd, data.envirement);
            free(command_path);
            perror("execve");
            exit(127);
        }
        waitpid(pid, NULL, 0); // had l waitpid kaytsna l command hta t executa lina
        return 0;
    }

    //hna radi  nHandliw multiple commands with pipes
    while (temp_nodes) {
        if (temp_nodes->cmd[0] == NULL) {
            temp_nodes = temp_nodes->next_node;
            continue;
        }

        if (temp_nodes->next_node) {
            pipe(pipe_fd); // Hna kancriyiw new pip ila kant xihaja next to it (next node != NULL)
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) { 
            //Saluma stp hna zidi fih redirection hitax mabrawx ikhdmou lili
            //////////////////////////////////HADI PARTIE D REDIRECTION ////////////////////////////////////////////////////
            if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1) {
                exit(EXIT_FAILURE);
            }

            
            if (temp_nodes->redir) {
             // hnaya hti fih l function hitax mabritx n 9is f lcode dyalek la t5ser xihaja  💗
            }

            if (temp_nodes->next_node) {
                dup2(pipe_fd[1], STDOUT_FILENO); // hnaya ka redirexti output l pipe
            }
            if (temp_nodes->prev_node) {
                dup2(in_fd, STDIN_FILENO); // kanredirecti  input from previous lcommand
            }
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (ft_check_builtins(temp_nodes->cmd[0]) == 1) {
               check_command(&data, temp_nodes); 
                exit(0);
            }

            char *command_path = find_command_path(temp_nodes->cmd[0], data.envirement);
            if (!command_path) {
                printf("%s: command not found\n", temp_nodes->cmd[0]);
                exit(127);
            }
            execve(command_path, temp_nodes->cmd, data.envirement);
            free(command_path);
            perror("execve");
            exit(127);
        } 
        else 
        { 
            if (temp_nodes->next_node) {
                close(pipe_fd[1]); 
            }
            if (temp_nodes->prev_node) {
                close(in_fd); 
            }
            in_fd = pipe_fd[0]; 
        }
        temp_nodes = temp_nodes->next_node;
    }

    dup2(in_fd, 0);
    close(in_fd);
    int i = 0;

    while (i < data.count_pips) {
        wait(NULL);
        i++;
    }
    return 0;
}

void fre_the_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next_token;
		free(current->data);
		free(current);
		current = next;
	}
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
		main3(g_minishell);
		// // fre_the_tokens(g_minishell.tokens);
		// free_node_list(g_minishell.nodes);
	}
    return 0;
}