#include "minishell.h"

int ft_input(t_token *tokens)
{
    t_token *current = tokens;
    // int fd;
    char *filename;

    // Find the input redirection token
    while (current)
    {
        printf(" \033[36m current --> %s \033[0m\n", current->data);
        if (current->data_type == INP_REDIR)  // '<' input redirect
        {
            printf(" \033[32m current --> %u \033[0m\n", current->data_type);
            printf(" \033[32m current->next_token --> %s \033[0m\n", current->next_token->data);
        //     // Check if there's a filename after the redirection token
            if (!current->next_token || !current->next_token->data)
                return (printf("syntax error near unexpected token '<'"));
            filename = current->next_token->data;
            
            // Check if file exists and is readable
            if (access(filename, R_OK) == -1) 
            {
                if (errno == ENOENT) 
                    return (printf("File does not exist\n"));
                else if (errno == EACCES) 
                    return (printf("Permission denied\n"));
                return (printf("Error accessing file\n"));
            }
        }
        //     // Open the file for reading
        //     fd = open(filename, O_RDONLY);
        //     if (fd < 0)
        //         return (printf("Error: Cannot open file\n"));

        //     // Redirect input to read from the file
        //     if (dup2(fd, STDIN_FILENO) == -1)
        //     {
        //         close(fd);
        //         return (printf("Error: Cannot redirect input\n"));
        //     }
        //     close(fd);

        //     return (0);
        // }
        current = current->next_token;
    }

    return (0);  // No input redirection found
}