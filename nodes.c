/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:41:02 by salaoui           #+#    #+#             */
/*   Updated: 2024/10/21 13:33:07 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	fill_redi(enum e_token_type token_t, char *red_file,
		t_redir **redirections)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->red_type = token_t;
	new_redir->file = ft_strdup(red_file);
	new_redir->next = NULL;
	ft_redi_add_back(redirections, new_redir);
}

void	ft_node_add_back(t_node **node_list, t_node *new_node)
{
	t_node	*arrs;

	arrs = *node_list;
	if (!node_list || !new_node)
		return ;
	if (*node_list == NULL)
	{
		*node_list = new_node;
		return ;
	}
	while (arrs->next_node != NULL)
		arrs = arrs->next_node;
	arrs->next_node = new_node;
	new_node->prev_node = arrs;
}

void	fill_node(t_token *temp_tokens, t_node **node_list)
{
	t_node	*node;
	t_redir	*redirections;
	t_token	*tokens;
	int		cmd_idx;
	int		i;

	i = 0;
	tokens = temp_tokens;
	redirections = NULL;
	node = malloc(sizeof(t_node));
	if (!node)
		return ;
	cmd_idx = cmd_count(temp_tokens);
	node->cmd = malloc(sizeof(char *) * (cmd_idx + 1));
	while (tokens && tokens->data_type != PIPE)
	{
		if (tokens->data_type == OUT_REDIR || tokens->data_type == APPEND
			|| tokens->data_type == INP_REDIR || tokens->data_type == HER_DOC)
		{
			fill_redi(tokens->data_type, tokens->next_token->data,
				&redirections);
			tokens = tokens->next_token;
		}
		else
			node->cmd[i++] = ft_strdup(tokens->data);
		tokens = tokens->next_token;
	}
	node->redir = redirections;
	node->cmd[i] = NULL;
	node->next_node = NULL;
	ft_node_add_back(node_list, node);
}

void	fill_commands(t_node **node_list, t_token *tokens)
{
	while (tokens)
	{
		fill_node(tokens, node_list);
		while (tokens && tokens->data_type != PIPE)
			tokens = tokens->next_token;
		if (tokens && tokens->data_type == PIPE)
			tokens = tokens->next_token;
	}
}

t_node	*mk_nodes(t_token *tokens)
{
	t_node	*nodes;
	t_token	*current;
	t_token	*next;
	int		cmd_count;

	nodes = NULL;
	current = tokens;
	cmd_count = count_pipe(tokens);
	fill_commands(&nodes, tokens);
	while (current)
	{
		cmd_count++;
		next = current->next_token;
		free(current->data);
		free(current);
		current = next;
	}
	return (nodes);
}
