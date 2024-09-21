
#include "minishell.h"
// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// typedef struct s_ali
// {
//     char **command;
// }t_ali;

// void    echo_arguments(char **av, int len)
// {
//     printf("ANA HNA");
//         int i;
//         int j;

//         i = 1;
//         j = 0;
//         while(i < len)
//         {
//             while(av[i][j])
//                 write(1, &av[i][j++], 1);
//             j = 0;
//             if (len != i + 1)
//                 write(1, " ", 1);
//             i++;
//         }
//         write(1, "\n", 1);
// }

void    echo_arguments1(t_minishell *prin, int len)
{
        int j = 0;
        t_token *current_token = prin->tokens; 
        while (current_token != NULL && j < len) {
            // printf("\nThis is the token data: %c<-----\n", current_token->data[j]);  
            while (current_token->data[j]) {
                write(1, &current_token->data[j++], 1);
            }
            
            j = 0; // Reset the inner counter for the next token

            // If there is another token, print a space
            if (current_token->next_token != NULL) {
                write(1, " ", 1);
            }
            
            // Move to the next token
            current_token = current_token->next_token;
        }

        // Print a newline at the end (if needed)
        write(1, "\n", 1);
}

        // printf("Ana f fun");

        // int i;
        // int j;

        // i = 2;
        // j = 0;
        // printf("\nAna daa5la n9ra mora -n, len %d\n", len);
        // printf("%s", data.tokens->data);
        // while(i < len)
        // {
        //     printf("\nthis is av[1]%c<-----\n", av[i][j]);
        //     i++;
        // }
        // while(i < len)
        // {
        //     while(av[i][j])
        //         write(1, &av[i][j++], 1);
        //     j = 0;
        //     if (len != i + 1)
        //         write(1, " ", 1);
        //     i++;
        // }
// }

int ft_echo(int len ,int ac, t_minishell data)
{ 
    (void)data;
    (void)ac;
    // t_minishell 
    // printf("\n len: \033[0;31m%d\033[0m\n", len);
    // printf("\n len: \033[0;33m%d\033[0m\n", ac);
    
    if (!ft_strncmp(data.tokens->data, "echo", 4) && data.tokens->data)
    {
        if (data.tokens->next_token == NULL)
            write(1, "\n", 1);
        else if (!ft_strncmp(data.tokens->next_token->data , "-",1))
        {
            if (!strncmp(&data.tokens->next_token->data[1], "n", 1))
            {
                // printf("\n\nl da5el d -->n<---\n");
                // while(data.tokens->next_token->data != NU)
                // {
                    len = ft_strlen(data.tokens->next_token->next_token->data);
                    // printf("\nhadi len---->%d\n", len);
                    echo_arguments1(&data, len);
                    // data.tokens->next_token->data = data.tokens->next_token->next_token->data;
                // }
            }
        }
    }
    // return(0);
    // if (!ft_strncmp(data.tokens->data, "echo", 4) && data.tokens->data && data.tokens->next_token != NULL)
    // if (!ft_strncmp(data.tokens->data, "echo", 4)  && data.tokens->data && data.tokens->next_token != NULL && )
    // {
    //     printf("s\n");
    //     // printf("\nthis is inside the fun%d\n", i);
    //     if (!strncmp(&data.tokens->data[1], "n", 1))
    //     {
    //         printf("s\n");
    //         echo_arguments1(&data.tokens->data, data.lenght_command);
    //     }
    //     // printf("%c", data.tokens->data[1]);      
    //     // else
    //     //     printf("aloha--->%c\n", data.tokens->data[2]);
    // }
    // else{
    // printf("2");
        // echo_arguments(data.tokens->data, ac);
    // }
    return(0);
}

