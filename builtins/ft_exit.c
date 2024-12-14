#include "../minishell.h"

int is_numeric(const char *str) {
    int i ;

    i = 0;
    if (!str || !*str)
        return 0;
    while(str[i])
    {
        if (!ft_isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+')))
            return 0;
        i++;
    }
    return 1;
}

void ft_exit(t_minishell *data)
{
    t_node *tmp_node = data->nodes;

    if (!tmp_node || !tmp_node->cmd) {
        printf("exit\n");
        exit(0);
    }

    printf("exit\n");

    int i = 0;
    while (tmp_node->cmd[i])
        i++;

    if (i > 2) {
        printf("bash: exit: too many arguments\n");
        data->exit_status = 1; 
        return;
    }

    if (i == 1) {
         free_nodes(data->nodes);
        exit(data->exit_status);
    }

    int j = 0;
    while (tmp_node->cmd[1][j] == ' ')
        j++;

    if (!is_numeric(&tmp_node->cmd[1][j])) {
        printf("bash: exit: %s: numeric argument required\n", tmp_node->cmd[1]);
        data->exit_status = 2;
             free_nodes(data->nodes);
        exit(data->exit_status);
    }

    data->exit_status = ft_atoi(&tmp_node->cmd[1][j]) % 256;
     free_nodes(data->nodes);
    exit(data->exit_status);
}
