/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:09:02 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/10 00:17:18 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(i == 0 && (str[i] == '-'
					|| str[i] == '+')))
			return (0);
		i++;
	}
	return (1);
}

int	handle_negative_exit_status(int status)
{
	if (status < 0)
		status = 256 + status;
	return (status);
}

int	get_exit_status(const char *status_str)
{
	int	status;

	status = ft_atoi(status_str);
	status = handle_negative_exit_status(status);
	return (status % 256);
}

int	parse_exit_argument(t_minishell *data, t_node *tmp_node)
{
	if (tmp_node->cmd[1])
	{
		if (!is_numeric(tmp_node->cmd[1]))
		{
			printf("bash: exit: %s: numeric argument required\n",
				tmp_node->cmd[1]);
			data->exit_status = 2;
			return (0);
		}
		data->exit_status = get_exit_status(tmp_node->cmd[1]);
	}
	else
	{
		data->exit_status = 0;
	}
	return (1);
}

void	ft_exit(t_minishell *data)
{
	t_node	*tmp_node;
	int		i;

	tmp_node = data->nodes;
	if (!tmp_node || !tmp_node->cmd)
	{
		printf("exit\n");
		exit(0);
	}
	i = 0;
	while (tmp_node->cmd[i])
		i++;
	if (i > 2)
	{
		printf("bash: exit: too many arguments\n");
		data->exit_status = 1;
		return ;
	}
	if (!parse_exit_argument(data, tmp_node))
	{
		exit(data->exit_status);
	}
	printf("exit\n");
	exit(data->exit_status);
}
