#include "../minishell.h"

// void	ft_exit(t_minishell *data)
// {
// 	t_token	*tmp_tokens;
// 	int		exit_status;

// 	tmp_tokens = data->tokens;
// 	exit_status = 0;
// 	if (tmp_tokens->next_token)
// 	{
// 		exit_status = ft_atoi(tmp_tokens->next_token->data);
// 		printf("%d", exit_status);
// 	}
// 	exit(exit_status);
// }
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Helper function to check if a string is numeric
int is_numeric(const char *str) {
    if (!str || !*str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+')))
            return 0;
    }
    return 1;
}

extern int g_exit_status;

void exit(t_minishell *data) {
	
    printf("exit\n");
	t_token	*tmp_tokens;

	tmp_tokens = data->tokens;

    if (tmp_tokens[1]) {
        if (is_numeric(tmp_tokens[1])) {
            g_exit_status = atoi(tmp_tokens[1]) % 256; // Store the exit status
        } else {
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", tmp_tokens[1]);
            g_exit_status = 2; // Error exit status
        }
    }
    exit(g_exit_status);
}


void execute_echo(char **args) {
    for (int i = 1; args[i]; i++) {
        if (args[i][0] == '$' && args[i][1] == '?') {
            char *status = resolve_variable("?");
            if (status) {
                printf("%s", status);
                free(status);
            }
        } else {
            printf("%s", args[i]);
        }
        if (args[i + 1])
            printf(" ");
    }
    printf("\n");
}
