#include "minishell.h"


void ft_input(int ac, char *av[])
{
 
	if (ac != 4 || strcmp(av[2], "<") != 0 )
    {
		write(2, "ALOHA", 5);
        exit(EXIT_FAILURE);
    }

    char *filename = av[3]; 
	
    // Check if the file exists and is readable
	if (access(filename, R_OK) == -1) {
			if (errno == ENOENT) {
				char *msg = "File does not exist\n";
				write(STDERR_FILENO, msg, strlen(msg));
			} else if (errno == EACCES) {
				char *msg = "Permission denied\n";
				write(STDERR_FILENO, msg, strlen(msg));
			}
			return ;
		}

    // Open the file for reading
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error: Cannot open file\n", 24);
        exit(EXIT_FAILURE);
    }

    // Redirect input to read from the file
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        write(2, "Error: Cannot redirect input\n", 29);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Read from file and write to STDOUT
    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    close(fd);
}
// int main(int ac, char *av[])
// {
	
//     ft_input(ac, av);
//     return 0;
// }

