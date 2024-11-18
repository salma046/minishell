#include "minishell.h"


// void ft_input(int ac, char *av[])
// {
 
// 	if (ac != 4 || strcmp(av[2], "<") != 0 )
//     {
// 		write(2, "ALOHA", 5);
//         exit(EXIT_FAILURE);
//     }

//     char *filename = av[3]; 
	
//     // Check if the file exists and is readable
// 	if (access(filename, R_OK) == -1) {
// 			if (errno == ENOENT) {
// 				char *msg = "File does not exist\n";
// 				write(STDERR_FILENO, msg, strlen(msg));
// 			} else if (errno == EACCES) {
// 				char *msg = "Permission denied\n";
// 				write(STDERR_FILENO, msg, strlen(msg));
// 			}
// 			return ;
// 		}

//     // Open the file for reading
//     int fd = open(filename, O_RDONLY);
//     if (fd < 0)
//     {
//         write(2, "Error: Cannot open file\n", 24);
//         exit(EXIT_FAILURE);
//     }

//     // Redirect input to read from the file
//     if (dup2(fd, STDIN_FILENO) == -1)
//     {
//         write(2, "Error: Cannot redirect input\n", 29);
//         close(fd);
//         exit(EXIT_FAILURE);
//     }

//     // Read from file and write to STDOUT
//     char buffer[1024];
//     ssize_t bytes_read;
//     while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
//     {
//         write(STDOUT_FILENO, buffer, bytes_read);
//     }
//     close(fd);
// }
// int main(int ac, char *av[])
// {
	
//     ft_input(ac, av);
//     return 0;
// }

int ft_input(t_token *tokens)
{
    t_token *current = tokens;
    int fd;
    char *filename;

    // Find the input redirection token
    while (current)
    {
        if (current->data_type == INP_REDIR)  // '<' input redirect
        {
            // Check if there's a filename after the redirection token
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

            // Open the file for reading
            fd = open(filename, O_RDONLY);
            if (fd < 0)
                return (printf("Error: Cannot open file\n"));

            // Redirect input to read from the file
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                close(fd);
                return (printf("Error: Cannot redirect input\n"));
            }
            close(fd);

            return (0);
        }
        current = current->next_token;
    }

    return (0);  // No input redirection found
}