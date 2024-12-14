/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:05:58 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/14 01:26:03 by saait-si         ###   ########.fr       */
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

	fre_the_tokens(g_minishell.tokens);
	
	current = node_list;
	while (current != NULL)
	{
		printf("[%s]\n", current->cmd[0]);
		
		next = current->next_node;
		free_node(current);
		current = next;
	}
}

void free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

void free_env_list(t_env *head)
{
	t_env *tmp;
	while (head)
	{
		tmp = head->next;
		free_env_node(head);
		head = tmp;
	}
}

void fre_the_tokens(t_token *tokens)
{
	t_token	*tmp;
	// t_token	*next;

	// current = tokens;
	while (tokens)
	{
		// printf("token : %s\n", current->data);
		tmp = tokens;
		tokens = tokens->next_token;
		printf("tmp %p\n", tmp);
		printf("tmp data %p--->%s\n", tmp->data, tmp->data);
		free(tmp->data);
		free(tmp);
	}
}
