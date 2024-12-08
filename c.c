#include "minishell.h"

int main3(t_minishell data) {
    t_node *temp_nodes = data.nodes;
    int pipe_fd[2] = {-1, -1};
    int in_fd = dup(STDIN_FILENO); // Backup stdin
    pid_t pid;

    while (temp_nodes) {
        if (temp_nodes->cmd[0] == NULL) {
            temp_nodes = temp_nodes->next_node;
            continue;
        }

        // Create a pipe for the current command if it's not the last node
        if (temp_nodes->next_node) {
            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                return 1;
            }
        }

        if (ft_check_builtins(temp_nodes->cmd[0])) {
            // Handle built-ins
            if (check_command(&data, temp_nodes) == 1 && temp_nodes->next_node == NULL) {
                // Built-in handled in the parent for the last command
                break;
            } else if (check_command(&data, temp_nodes) == 0) {
                // Built-in executed in a child for intermediate commands
                close(pipe_fd[1]); // Close write end of the pipe
                close(pipe_fd[0]); // Close read end of the pipe
                continue;
            }
        } else {
            // Fork a new process for non-built-in commands
            pid = fork();
            if (pid == -1) {
                perror("fork");
                return 1;
            }
            if (pid == 0) { // Child process
                if (temp_nodes->next_node) {
                    dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe's write end
                }
                dup2(in_fd, STDIN_FILENO); // Redirect stdin to previous pipe's read end
                close(pipe_fd[0]);
                close(pipe_fd[1]);
                close(in_fd);

                // Execute non-built-in commands
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
        }

        // Parent process
        close(pipe_fd[1]); // Close write end of the pipe
        close(in_fd);      // Close the previous stdin
        in_fd = pipe_fd[0]; // Set the new stdin for the next command
        temp_nodes = temp_nodes->next_node;
    }

    close(in_fd); // Close the final stdin

    // Wait for all child processes
    int status;
    while (wait(&status) > 0);

    return 0;
}
