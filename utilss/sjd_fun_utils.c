#include "../minishell.h"


int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1)
    {
        return (-1);
    }
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
} 

void ft_sigint(int x)
{
    (void)x;
	static int i;
	if (i == 0)
		write(1, "~$\n~$", 6);
	else 
		write(1, "~$^C \n~$", 8);
}
