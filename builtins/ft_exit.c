#include "../minishell.h"

int is_numeric(const char *str) {
    int i ;

    i = 0;
    if (!str || !*str)
        return 0;
   
    while(str[i])
    {
        if (!ft_isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+')))
        {
            printf("hello");
            return 0;
        }
        if (str[i] == '-')
        {
            printf("nega");
            exit (0);
        }
        i++;
    }
    return 1;
}


void ft_exit(t_minishell *data)
{
	printf("---\033[1;35m Ana f exit \033[0m\n---");
	t_node	*tmp_node;
	tmp_node = data->nodes;
      if (!tmp_node || !tmp_node->cmd) {
        printf("exit\n");
        exit(0);
    }
    int i = 0;
    while (tmp_node->cmd[i]) {
        i++;
    }
    
    if (i > 2) 
    {
        if (!is_numeric(tmp_node->cmd[1]))
        {
            printf("bash: exit: %s: numeric argument required\n", tmp_node->cmd[1]);
            exit(data->exit_status);
        }
        data->exit_status = 2;
        return;  
    }
    if (tmp_node->cmd[1])
	{
        printf("\033[1;35m%d\033[0m", is_numeric(tmp_node->cmd[1]));
        if (is_numeric(tmp_node->cmd[1])) {
        
            // printf("before:%d\n", data->exit_status);
            data->exit_status = ft_atoi(tmp_node->cmd[1]) % 256; 
            // printf("aftere:%d\n", data->exit_status);
        } 
        else
        {
            printf("bash: exit: %s: numeric argument required\n", tmp_node->cmd[1]);
            data->exit_status  = 2;
            exit(data->exit_status);
        }
    }
    exit(data->exit_status);
        // printf("fiin:%d\n", data->exit_status);
}