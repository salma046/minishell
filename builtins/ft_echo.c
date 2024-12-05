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

void ft_check_n_flag(char **cmd, int *flag, int *start_index)
{
    *flag = 0;
    *start_index = 1;

    // Check if first argument is -n or starts with -n
    while (cmd[*start_index] && strncmp(cmd[*start_index], "-n", 2) == 0)
    {
        char *str = cmd[*start_index];
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
            (*start_index)++;
        }
        else
            break;
    }
}

void ft_echo(t_node *node)
{
    int flag = 0;
    int start_index = 1;

    // No command or only "echo"
    if (!node->cmd || !node->cmd[1])
    {
        write(1, "\n", 1);
        return;
    }

    // Check for -n flag
    ft_check_n_flag(node->cmd, &flag, &start_index);

    // If no arguments left after -n flags
    if (!node->cmd[start_index])
        return;

    // Print remaining arguments
    int i = start_index;
    while (node->cmd[i])
    {
        write(1, node->cmd[i], ft_strlen(node->cmd[i]));
        if (node->cmd[i + 1] != NULL)
            write(1, " ", 1);
        i++;
    }

    // Add newline if -n flag was not set
    if (!flag)
        write(1, "\n", 1);
}

