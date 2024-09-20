
#include "minishell.h"
// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// typedef struct s_ali
// {
//     char **command;
// }t_ali;

void    echo_arguments(char **av, int len)
{
    printf("ANA HNA");
        int i;
        int j;

        i = 1;
        j = 0;
        while(i < len)
        {
            while(av[i][j])
                write(1, &av[i][j++], 1);
            j = 0;
            if (len != i + 1)
                write(1, " ", 1);
            i++;
        }
        write(1, "\n", 1);
}

void    echo_arguments1(char **av, int len)
{
        printf("aloha");
        int i;
        int j;

        i = 2;
        j = 0;
        printf("hadi hiya len:%d", len);
        while(i < len)
        {
             printf("aloha");

            while(av[i][j])
                write(1, &av[i][j++], 1);
            j = 0;
            if (len != i + 1)
                write(1, " ", 1);
            i++;
        }
}

int ft_echo(int i, t_minishell data)
{ i = data.lenght_command;
    printf("\nthis is inside the fun%d\n", i);
    // if(i == 0)
    // {
    //     if (!ft_strncmp(data.tokens->data, "echo", 7) && data.tokens->data)
    //         write(1, "\n", 1);
    //     return(0);
    // }
    if (data.tokens->data[0] == '-')
    {
        // printf("s");
        printf("\nthis is inside the fun%d\n", i);
        if (!strncmp(&data.tokens->data[1], "n", 1))
            echo_arguments1(&data.tokens->data, data.lenght_command);
        // printf("%c", data.tokens->data[1]);      
        // else
        //     printf("aloha--->%c\n", data.tokens->data[2]);
    }
    // else{
    // printf("2");
    //     echo_arguments(data.tokens->data, ac);
    // }
    return(0);
}

