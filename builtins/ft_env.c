/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:01:46 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/10 02:49:44 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_node *node, t_minishell **data)
{
	t_env	*tmp;

	node = (*data)->nodes;
	tmp = (*data)->envir;
	// printf ("[%s]\n", node->cmd[0]);
	// printf ("[%s]\n", node->cmd[1]);
	if (tmp && node->cmd[1] == NULL)
	{
		while (tmp)
		{
			if (tmp->value != NULL)
			{
				write(node->out_file, tmp->key, ft_strlen(tmp->key));
				write(node->out_file, "=", 1);
				write(node->out_file, tmp->value, ft_strlen(tmp->value));
				write(node->out_file, "\n", 1);
			}
			tmp = tmp->next;
		}
	}
	else
		printf ("env: %s: No such file or directory\n", node->cmd[1]);
}
