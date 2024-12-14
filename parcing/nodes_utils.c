/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:59:24 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/14 00:53:22 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redi_add_back(t_redir **redirections, t_redir *new_redir)
{
	t_redir	*arrs;

	arrs = *redirections;
	if (!redirections || !new_redir)
		return ;
	if (*redirections == NULL)
	{
		*redirections = new_redir;
		return ;
	}
	while (arrs->next != NULL)
		arrs = arrs->next;
	arrs->next = new_redir;
}

t_node	*allocate_for_node(t_token *temp_tokens)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(node));
	node->cmd = malloc(sizeof(char *) * (cmd_count(temp_tokens) + 1));
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	ft_bzero(node->cmd , sizeof(node->cmd));
	return (node);
}

int	cmd_count(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->data_type != PIPE)
	{
		if (tokens->data_type == OUT_REDIR || tokens->data_type == APPEND
			|| tokens->data_type == INP_REDIR || tokens->data_type == HER_DOC)
			tokens = tokens->next_token;
		else
		{
			i++;
		}
		tokens = tokens->next_token;
	}
	return (i);
}

int	count_pipe(t_node *nodes)
{
	t_node	*temp_node;
	int		count;

	temp_node = nodes;
	count = 0;
	while (temp_node)
	{
		count++;
		temp_node = temp_node->next_node;
	}
	// count++;
	return (count);
}
