/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:05:58 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/14 05:03:28 by saait-si         ###   ########.fr       */
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
//Sojod
void free_nodes(t_node *node)
{
    t_node *tmp;

    while (node)
    {
        tmp = node->next_node;

        // Free cmd array
        if (node->cmd)
        {
            for (int i = 0; node->cmd[i]; i++)
                free(node->cmd[i]);
            free(node->cmd);
        }

        // Free redir structure if needed
        if (node->redir)
            free(node->redir);

        // Close file descriptors if open
        if (node->out_file > 0)
            close(node->out_file);
        if (node->in_file > 0)
            close(node->in_file);

        // Free the node itself
        free(node);
        node = tmp;
    }
}
///
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
		// printf("tmp %p\n", tmp);
		// printf("tmp data %p--->%s\n", tmp->data, tmp->data);
		free(tmp->data);
		free(tmp);
	}
}
