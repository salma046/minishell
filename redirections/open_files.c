#include "../minishell.h"

int ft_input(char *file_name, t_node *node)
{
    node->in_file = open(file_name, O_RDONLY);
    // node->out_file = open("/tmp/hiii.txt", O_RDWR | O_CREAT | O_TRUNC | O_EXCL, 0644);
    if (node->in_file == -1)
	{
        //to save my exit number cause it's a std err
		perror("fd");
		return (-1);
	}
    return (0);
}

int ft_output(char *file_name, t_node *node)
{
    node->out_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (node->out_file == -1)
	{
        //to save my exit number cause it's a std err
		perror("fd");
		return (-1);
	}
    return (0);
}

int ft_append(char *file_name, t_node *node)
{
		dprintf(2,"ihiiii\n");
    node->out_file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (node->out_file == -1)
	{
        //to save my exit number cause it's a std err
		perror("fd");
		return (-1);
	}
    return (0);
}
