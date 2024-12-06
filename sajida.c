#include "./minishell.h"

char    *aloha(char *command, char **env){

    char *path_env = NULL;
    char full_path[1024];
    int i = 0, j = 0, k = 0;

    while (env[i] != NULL) {
        if (strncmp(env[i], "PATH=", 5) == 0) {
            path_env = env[i] + 5; 
        }
        i++;
    }

    if (!path_env) {
        errno = ENOENT;
        perror("PATH not found");
        return NULL;
    }
    i = 0;
    while (path_env[i] != '\0') {
        memset(full_path, 0, sizeof(full_path));
        k = 0;

        while (path_env[i] != ':' && path_env[i] != '\0') {
            full_path[k++] = path_env[i++];
        }

        full_path[k++] = '/';
        j = 0;
        while (command[j] != '\0') {
            full_path[k++] = command[j++];
        }
        full_path[k] = '\0';

        if (access(full_path, X_OK) == 0) {
            return strdup(full_path);
        }

        if (path_env[i] == ':')
            i++;
    }
    errno = ENOENT;
    perror("Command not found");
    return NULL;
}

int hadi_one(t_token *data, char **env)
{
    char *command_path;
    char **args;
    int arg_count = 0;
    t_token *current = data;
    pid_t  pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
    while (current != NULL) {
        arg_count++;
        current = current->next_token;
    }
    args = malloc((arg_count + 1) * sizeof(char *));
    if (!args) {
        perror("malloc");
        exit(1);
    }

    current = data;
    int i = 0;
    while(i < arg_count)
    {
        args[i] = current->data;
        current = current->next_token;
        i++;
    }
    args[arg_count] = NULL;
    command_path = find_command_path(args[0], env);
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork");
        free(command_path);
        free(args);
        exit(1);
    }
        execve(args[0], args, env);
        printf("\033[1;35m======\033[0m");
        if (execve(command_path, args, env) == -1)
        {
            perror("execve");
            free(command_path);
            free(args);
            exit(1);
            printf("\033[1;35m======\033[0m");
        }
        free(command_path);
        free(args);
    } else
    {
        waitpid(pid, &status, 0);
        if (status >> 8 != 0) {
            perror("Command execution failed");
        }
    }
    return 0;
    } 
     
