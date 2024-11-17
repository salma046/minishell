#include "minishell.h"



int ft_output(t_token *tokens)
{
    t_token *current = tokens;
    int fd;
    int original_stdout;
    pid_t pid;
    char *cmd;

    // Store the command before searching for redirection
    cmd = tokens->data;

    // Find the redirection token (OUT_REDIR)
    while (current && current->data_type != OUT_REDIR)
        current = current->next_token;

    // Check if we found '>' and if there's a next token (filename)
    if (!current || !current->next_token)
    {
        printf("I need the file name please :)\n");
        return 1;
    }

    // Save original stdout
    original_stdout = dup(STDOUT_FILENO);
    if (original_stdout == -1)
    {
        perror("dup");
        return 1;
    }

    // Open the file
    fd = open(current->next_token->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("fd");
        close(original_stdout);
        return 1;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(fd);
        close(original_stdout);
        return 1;
    }

    if (pid == 0)  
    {
        // Redirect stdout to file
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fd);
        
        // Execute the command
        if (execlp(cmd, cmd, NULL) == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    else  // Parent process == waiting for the pid process to end
    {
        int status;
        waitpid(pid, &status, 0);
        close(fd);
        
        // Restore original stdout haka
        if (dup2(original_stdout, STDOUT_FILENO) == -1)
        {
            perror("dup2");
        }
        close(original_stdout);
    }
	printf("KOULXI HOWA HADAk");
	return 0;
}