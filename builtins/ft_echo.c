#include "../minishell.h"

void	ft_print(t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd[i])
	{
		write(1, node->cmd[i], ft_strlen(node->cmd[i]));
		if (node->cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int	is_valid_n_flag(char *str)
{
	int	i;

	i = 2;
	if (strncmp(str, "-n", 2) != 0)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_n_flag(char **cmd, int *flag, int *start)
{
	*flag = 0;
	*start = 1;
	while (cmd[*start] && is_valid_n_flag(cmd[*start]))
	{
		*flag = 1;
		(*start)++;
	}
}

void	ft_echo(t_node *node)
{
	int	flag;
	int	start_index;
	int	i;

	flag = 0;
	start_index = 1;
	if (!node->cmd || !node->cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
	ft_check_n_flag(node->cmd, &flag, &start_index);
	if (!node->cmd[start_index])
		return ;
	i = start_index;
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
