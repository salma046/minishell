/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:05:58 by salaoui           #+#    #+#             */
/*   Updated: 2024/11/24 10:12:46 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir_list(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current != NULL)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
}

void	free_node(t_node *node)
{
	int	i;

	i = 0;
	if (node->cmd)
	{
		while (node->cmd[i])
		{
			free(node->cmd[i]);
			i++;
		}
		free(node->cmd);
	}
	if (node->redir)
	{
		free_redir_list(node->redir);
	}
	free(node);
}

void	free_node_list(t_node *node_list)
{
	t_node	*current;
	t_node	*next;

	current = node_list;
	while (current != NULL)
	{
		next = current->next_node;
		free_node(current);
		current = next;
	}
}
