#include "../minishell.h"

void ft_print(t_node *node)
{
    int i = 0;
    
    while (node->cmd[i])
    {
        write(1, node->cmd[i], ft_strlen(node->cmd[i]));
        if (node->cmd[i + 1] != NULL)
            write(1, " ", 1);
        i++;
    }
}

void ft_check_n_flag(char **cmd, int *flag, int *start)
{
    *flag = 0;
    *start = 1;

    while (cmd[*start] && strncmp(cmd[*start], "-n", 2) == 0)
    {
        char *str = cmd[*start];
        int i = 2;  
        int all_n = 1;  

        while (str[i] != '\0')
        {
            if (str[i] != 'n')
            {
                all_n = 0;  
                break;
            }
            i++;
        }
        if (all_n)
        {
            *flag = 1;
            (*start)++;
        }
        else
            break;
    }
}

void ft_echo(t_node *node, t_minishell *data)
{
    int flag = 0;
    int start_index = 1;

    if (!node->cmd || !node->cmd[1])
    {
        write(1, "\n", 1);
        return;
    }
    if (!ft_strcmp(node->cmd[1], "$?"))
    {
        printf("sojod");
        data->g_exit_status = 2;
        printf("%d\n", data->g_exit_status);
    }
    else 
    {
        ft_check_n_flag(node->cmd, &flag, &start_index);

        if (!node->cmd[start_index])
            return;

        int i = start_index;
        while (node->cmd[i])
        {
            write(1, node->cmd[i], ft_strlen(node->cmd[i]));
            if (node->cmd[i + 1] != NULL)
                write(1, " ", 1);
            i++;
        }
        if (!flag)
            write(1, "\n", 1);
    }
}

// char *resolve_variable(t_minishell *data) 
// {
//     t_node	*tmp_node;

// 	tmp_node = data->nodes;
//     if (strcmp(tmp_node->cmd[0], "?") == 0) {
//         char *status = malloc(12); // Allocate space for the status
//         if (!status)
//             return NULL;
//         snprintf(status, 12, "%d", data->g_exit_status);
//         return status; 
//     }
//     return NULL;
// }

// void execute_echo(t_node **cmd_opr) 
// {
//     t_node *node;

//     node = *cmd_opr;
//     for (int i = 1; node->cmd[i]; i++) {
//         if (node->cmd[i][0] == '$' && node->cmd[i][1] == '?') {
//             char *status = resolve_variable("?");
//             if (status) {
//                 printf("%s", status);
//                 free(status);
//             }
//         } else {
//             printf("%s", node->cmd[i]);
//         }
//         if (node->cmd[i + 1])
//             printf(" ");
//     }
//     printf("\n");
// }

// char *resolve_variable(const char *var) {

//     t_minishell *data;

//     if (strcmp(var, "?") == 0) {
//         char *status = malloc(12); // Allocate space for the status
//         if (!status)
//             return NULL;
//         snprintf(status, 12, "%d", data->g_exit_status);
//         return status; 
//     }

//     return NULL;
// }

// void execute_echo(char **args) {
//     for (int i = 1; args[i]; i++) {
//         if (args[i][0] == '$' && args[i][1] == '?') {
//             char *status = resolve_variable("?");
//             if (status) {
//                 printf("%s", status);
//                 free(status);
//             }
//         } else {
//             printf("%s", args[i]);
//         }
//         if (args[i + 1])
//             printf(" ");
//     }
//     printf("\n");
// }
