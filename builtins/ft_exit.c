#include "../minishell.h"

int is_numeric(const char *str) {
    if (!str || !*str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (!ft_isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+')))
            return 0;
    }
    return 1;
}


void ft_exit(t_minishell *data)
{
	printf("hiiiiiii\n");
	t_node	*tmp_node;
	tmp_node = data->nodes;
      if (!tmp_node || !tmp_node->cmd) {
        printf("exit\n");
        exit(0);
    }
    if (tmp_node->cmd[2])
    {
        printf("bash: exit: %s: too many args\n", tmp_node->cmd[1]); // checking the output dyal bash 
        data->exit_status  = 2;
        // printf("\033[36mexit status:%d\033[0m\n", data->exit_status);
        // exit(data->exit_status);
    }
    if (tmp_node->cmd[1])
	{
        if (is_numeric(tmp_node->cmd[1])) {
        
            // printf("before:%d\n", data->exit_status);
            data->exit_status = atoi(tmp_node->cmd[1]) % 256; 
            // printf("aftere:%d\n", data->exit_status);

        } 
        else 
        {
            printf("bash: exit: %s: just numeric argument required\n", tmp_node->cmd[1]);
            data->exit_status  = 2;
        }
    }
    exit(data->exit_status);
            printf("fiin:%d\n", data->exit_status);
}
