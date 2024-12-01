#include "../minishell.h"

char    *find_command_path(char *command, char **env){

        printf("\033[0;31mcommand:%s\033[0m\n", command);
        char *path_env = NULL;
        char full_path[1024];
        int i = 0, j = 0, k = 0;

        while (env[i] != NULL) 
        {
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
        while (path_env[i] != '\0') 
        {
            ft_memset(full_path, 0, sizeof(full_path));
            k = 0;

            while (path_env[i] != ':' && path_env[i] != '\0') {
                full_path[k++] = path_env[i++];
            }
            full_path[k++] = '/';
            j = 0;
            // printf("\033[0;33mcommand:%s\033[0m", command);
            while (command[j] != '\0') {
                full_path[k++] = command[j++];
            }
            // printf("====>full_path:%s\n", full_path);
            full_path[k] = '\0';

            if (access(full_path, X_OK) == 0) {
                return ft_strdup(full_path);
            }
            if (path_env[i] == ':')
                i++;
        }
        errno = ENOENT;
    return NULL;
}

int ft_execute(t_token *data, char **env) {
    char *command_path;
    char **args;
    int arg_count = 0;
    t_token *current = data;

    while (current != NULL) {
        arg_count++;
        current = current->next_token;
    }

    args = malloc((arg_count + 1) * sizeof(char *));
    if (!args) {
        perror("malloc");
        return -1;  
    }

    current = data;
    int i = 0;
    while(i < arg_count) {
        args[i] = current->data;
        current = current->next_token;

        i++;
    }
    args[arg_count] = NULL;

    command_path = find_command_path(args[0], env);
    if (!command_path) {
        printf("%s: command not found\n", args[0]);
        free(args);
        return 127;  
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork");
        free(command_path);
        free(args);
        return -1;
    }
    else if (pid == 0) {
        if (execve(command_path, args, env) == -1) {
            perror("execve");
            free(command_path);
            free(args);
            exit(1);
        }
    } 
    else
    {
        int status;
        waitpid(pid, &status, 0);
        
        if (status >> 8 != 0) {
            perror("Command execution failed");
        }
    }
    return 0;
}