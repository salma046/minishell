#include "minishell.h"

t_minishell	g_minishell;
int main3(t_minishell data) {
    t_node *temp_nodes = data.nodes;
    int pipe_fd[2] = {-1, -1};
    int in_fd = dup(STDIN_FILENO);
    pid_t pid;

    // Check if there's only one command
    if (temp_nodes != NULL && temp_nodes->next_node == NULL) {
        // Handle single command execution
        if (ft_check_builtins(temp_nodes->cmd[0]) == 1) {
            if (check_command(&data, temp_nodes) == 1)
                printf("Executing built-in command: %s\n", temp_nodes->cmd[0]);
            return 0; // Exit after executing built-in
        }

        // Fork and execute the command
        pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }
        if (pid == 0) {
            // Handle redirections if any
            if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1)
                exit(EXIT_FAILURE);
            // Handle output redirection
            if (temp_nodes->redir && ft_check_redirections(temp_nodes) == 0) {
                // Implement redirection handling here
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
        // Wait for the child process to finish
        waitpid(pid, NULL, 0);
        return 0; // Exit after executing single command
    }

    // Handle multiple commands with pipes
    while (temp_nodes) {
        if (temp_nodes->cmd[0] == NULL) {
            temp_nodes = temp_nodes->next_node;
            continue;
        }

        if (temp_nodes->next_node) {
            pipe(pipe_fd); // Create a pipe if there's a next command
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) { // Child process
            if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1) {
                exit(EXIT_FAILURE);
            }

            // Handle input/output redirection
            if (temp_nodes->redir) {
                // Implement redirection handling here
            }

            if (temp_nodes->next_node) {
                dup2(pipe_fd[1], STDOUT_FILENO); // Redirect output to pipe
            }
            if (temp_nodes->prev_node) {
                dup2(in_fd, STDIN_FILENO); // Redirect input from previous command
            }

            // Check for built-in commands
            if (ft_check_builtins(temp_nodes->cmd[0]) == 1) {
               check_command(&data, temp_nodes); // Implement this function
                exit(0);
            }

            // Execute external command
            char *command_path = find_command_path(temp_nodes->cmd[0], data.envirement);
            if (!command_path) {
                printf("%s: command not found\n", temp_nodes->cmd[0]);
                exit(127);
            }
            execve(command_path, temp_nodes->cmd, data.envirement);
            free(command_path);
            perror("execve");
            exit(127);
        } else { // Parent process
            if (temp_nodes->next_node) {
                close(pipe_fd[1]); // Close write end of the pipe
            }
            if (temp_nodes->prev_node) {
                close(in_fd); // Close previous input
            }
            in_fd = pipe_fd[0]; // Save read end for the next command
        }

        temp_nodes = temp_nodes->next_node;
    }

    dup2(in_fd, 0);
    close(in_fd);
    
    // Wait for all child processes to finish
    for (int i = 0; i < data.count_pips; i++) {
        wait(NULL);
    }

    return 0;
}
// int main3(t_minishell data)
// {
//     t_node *temp_nodes = data.nodes;
// 	// In this line we have to check the command and build alone:
// 	if (check_command(&data, temp_nodes) == 0 && temp_nodes->next_node == NULL && temp_nodes != NULL)
// 	{
// 		printf(" \033[0;31m hna marasox iw9e3 walo \033[0m\n");
// 	}
// 	else 
// 	{
// 		int pipe_fd[2] = {-1, -1};
// 		int in_fd = dup(STDIN_FILENO);
// 		pid_t pid;

// 		while (temp_nodes)
// 		{
// 			if (temp_nodes->cmd[0] == NULL)
// 			{
// 				temp_nodes = temp_nodes->next_node;
// 				continue;
// 			}
// 			else
// 				pipe(pipe_fd);
// 			if (ft_check_builtins(temp_nodes->cmd[0]) == 1)
// 			{
// 				if (check_command(&data, temp_nodes) == 1)
// 					printf("Lda5erl");
// 			}
				
// 			pid = fork();
			
// 			if (pid == -1)
// 			{
// 				perror("fork");
// 				return 1;
// 			}
// 			if (pid == 0) 
// 			{
// 				if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1)
// 					exit(EXIT_FAILURE);
// 				if (temp_nodes->next_node)
// 				{
// 					dup2(pipe_fd[1], STDOUT_FILENO); // Redirect output to pipe.
// 					close(pipe_fd[1]);
// 					close(pipe_fd[0]);
// 					close(in_fd);
// 				}
// 				if (temp_nodes->redir && ft_check_redirections(temp_nodes) == 0)
// 				{
// 					if (temp_nodes->redir->red_type == OUT_REDIR || temp_nodes->redir->red_type == APPEND)
// 					{
// 						dup2(temp_nodes->out_file, STDOUT_FILENO);
// 						close(temp_nodes->out_file);
// 					}
// 					if (temp_nodes->redir->red_type == INP_REDIR)
// 					{
// 						dup2(temp_nodes->in_file, STDIN_FILENO);
// 						close(temp_nodes->in_file);
// 					}
// 				}
// 			// 5as hna bzaff d cmds:
				
				
// 					char *command_path = find_command_path(temp_nodes->cmd[0], data.envirement);
// 					if (!command_path)
// 					{
// 						printf("%s: command not found\n", temp_nodes->cmd[0]);
// 						exit(127);
// 					}
// 					execve(command_path, temp_nodes->cmd, data.envirement);
// 					free(command_path);
// 					perror("execve");
// 					exit(127);
				
// 			}
// 			temp_nodes = temp_nodes->next_node;
// 			dup2(pipe_fd[0],STDIN_FILENO);
// 			close(pipe_fd[0]); // Close unused read end in the child.
// 			close(pipe_fd[1]);
// 		}
// 		dup2(in_fd,0);
// 		close(in_fd);
// 		int	i;
// 		int	st;
// 		int	stt;
// 		pid_t	id;
// 		i = 0;
// 		while(i < data.count_pips)
// 		{
// 			id = waitpid(-1,&st,0);
// 			if(id == -1)
// 				break ;
// 			if(id == pid)
// 			{
// 				if(WIFEXITED(st))
// 					stt = WEXITSTATUS(st);
// 			}
// 			i++;
// 		}
// 	}
// 	// exit(1);
//     return 0;
// }

// int main3(t_minishell data)
// {
//     t_node *temp_nodes = data.nodes;
//     int pipe_fd[2] = {-1, -1};
//     int in_fd = dup(STDIN_FILENO);
//     pid_t pid;
//     int previous_pipe_read = -1;

//     while (temp_nodes)
//     {
//         if (temp_nodes->cmd[0] == NULL)
//         {
//             temp_nodes = temp_nodes->next_node;
//             continue;
//         }

//         if (temp_nodes->next_node)
//         {
//             if (pipe(pipe_fd) == -1)
//             {
//                 perror("pipe");
//                 return 1;
//             }
//         }

//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             return 1;
//         }

//         if (pid == 0) 
//         {
//             // Child process
            
//             // Handle input redirection from previous pipe
//             if (previous_pipe_read != -1)
//             {
//                 dup2(previous_pipe_read, STDIN_FILENO);
//                 close(previous_pipe_read);
//             }

//             // Handle redirections
//             if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1)
//                 exit(EXIT_FAILURE);

//             // Handle output redirection to next pipe
//             if (temp_nodes->next_node)
//             {
//                 dup2(pipe_fd[1], STDOUT_FILENO);
//                 close(pipe_fd[0]);
//                 close(pipe_fd[1]);
//             }

//             // Handle file redirections
//             if (temp_nodes->redir && ft_check_redirections(temp_nodes) == 0)
//             {
//                 if (temp_nodes->redir->red_type == OUT_REDIR || temp_nodes->redir->red_type == APPEND)
//                 {
//                     dup2(temp_nodes->out_file, STDOUT_FILENO);
//                     close(temp_nodes->out_file);
//                 }
//                 if (temp_nodes->redir->red_type == INP_REDIR)
//                 {
//                     dup2(temp_nodes->in_file, STDIN_FILENO);
//                     close(temp_nodes->in_file);
//                 }
//             }

//             // Handle builtin commands
//             if (ft_check_builtins(temp_nodes->cmd[0]) == 1)
//                 check_command(&data, temp_nodes);
//             else
//             {
//                 // Handle external commands
//                 char *command_path = find_command_path(temp_nodes->cmd[0], data.envirement);
//                 if (!command_path)
//                 {
//                     fprintf(stderr, "%s: command not found\n", temp_nodes->cmd[0]);
//                     exit(127);
//                 }
//                 execve(command_path, temp_nodes->cmd, data.envirement);
//                 free(command_path);
//                 perror("execve");
//                 exit(127);
//             }
//         }
//         else 
//         {
//             // Parent process
//             if (previous_pipe_read != -1)
//                 close(previous_pipe_read);

//             if (temp_nodes->next_node)
//             {
//                 previous_pipe_read = pipe_fd[0];
//                 close(pipe_fd[1]);
//             }
//         }

//         temp_nodes = temp_nodes->next_node;
//     }

//     // Close remaining file descriptors
//     if (previous_pipe_read != -1)
//         close(previous_pipe_read);
    
//     dup2(in_fd, STDIN_FILENO);
//     close(in_fd);

//     // Wait for child processes
//     int i = 0;
//     int st, stt;
//     pid_t id;
//     while (i < data.count_pips)
//     {
//         id = waitpid(-1, &st, 0);
//         if (id == -1)
//             break;
        
//         if (id == pid)
//         {
//             if (WIFEXITED(st))
//                 stt = WEXITSTATUS(st);
//         }
//         i++;
//     }

//     return 0;
// }
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