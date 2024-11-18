#include "minishell.h"

int ft_input(t_token *tokens)
{
    t_token *current = tokens;
    int fd;
    int original_stdin;
    pid_t pid;
    char *cmd;

    // storing the comd
    cmd = tokens->data;

    // Finding the <
    while (current && current->data_type != INP_REDIR)
        current = current->next_token;

    // looking for the file nameeeee
    if (!current || !current->next_token)
    {
        printf("I need the file name please :)\n");
        return 1;
    }

    // Save original stdin bax matmxix liyaaaaa
    original_stdin = dup(STDIN_FILENO);
    if (original_stdin == -1)
    {
        perror("dup");
        return 1;
    }

    fd = open(current->next_token->data, O_RDONLY);
    if (fd == -1)
    {
        perror("fd");
        close(original_stdin);
        return 1;
    }
    // hna radi ntsnaw had lprocess dyal l inout hta tsali bax makitisx liya 
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(fd);
        close(original_stdin);
        return 1;
    }

    if (pid == 0)  
    {
        // had l inout radi nhtoha f STDIN_FILE
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fd);
        
        // Hadi mn be3d radi thyed bax maywlix liya bzaf d sig
        if (execlp(cmd, cmd, NULL) == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    else  // hna radi tnsnaw hta tsali l process (pareny)
    {
        int status;
        waitpid(pid, &status, 0);
        close(fd);
        
        // Hna hadi nrj3o dakxi kima kan
        if (dup2(original_stdin, STDIN_FILENO) == -1)
        {
            perror("dup2");
        }
        close(original_stdin);
    }
    return 0;
}