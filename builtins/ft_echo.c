/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:56:34 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/09 23:57:32 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	check_all_n(char *str, int *all_n)
{
	int	i;

	i = 2;
	*all_n = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
		{
			*all_n = 0;
			break ;
		}
		i++;
	}
}

void	ft_check_n_flag(char **cmd, int *flag, int *start)
{
	char	*str;
	int		all_n;

	*flag = 0;
	*start = 1;
	while (cmd[*start] && ft_strncmp(cmd[*start], "-n", 2) == 0)
	{
		str = cmd[*start];
		check_all_n(str, &all_n);
		if (all_n)
		{
			*flag = 1;
			(*start)++;
		}
		else
		{
			break ;
		}
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
