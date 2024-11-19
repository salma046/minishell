// #include "minishell.h"



// void ft_execute(t_minishell *data)
// {
// 	t_node *node = data->nodes;
// 	if (!node || !node->cmd[0] || !node->cmd)
// 	{
// 		printf("ERROR: arguments");
// 		exit(EXIT_FAILURE);
// 	}

// 	pid_t pid = fork();

// 	if (pid == -1)
// 	{
// 		perror("ERROR IN FORk()");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		if (execve(node->cmd[0], node->cmd, data->envirement) == -1)
// 		{
// 			perror("execve FAILER");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else { // Parent process
//         int status;
//         // Wait for the child process to complete
//         if (waitpid(pid, &status, 0) == -1) {
//             perror("Error waiting for child process");
//         }
//     }
// }
#include "../minishell.h"

void ft_execute(t_minishell *data)
{
    // Access the first command node
    t_node *node = data->nodes;

    // Check that node and cmd are not NULL before execution
    // if (!node || !node->cmd || !node->cmd[0]) {
    //     fprintf(stderr, "Error: Command not found or empty.\n");
    //     return;
    // }

    // Fork the process
    pid_t pid = fork();
    if (pid == -1) {
        perror("ERROR IN FORK()");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // Child process
        // Execute the command
        if (execve(node->cmd[0], node->cmd, data->envirement) == -1) {
            perror("execve FAILURE");
            exit(EXIT_FAILURE); // Exit if execve fails
        }
    }
    else { // Parent process
        int status;
        // Wait for the child process to complete
        if (waitpid(pid, &status, 0) == -1) {
            perror("Error waiting for child process");
        }
    }
}
