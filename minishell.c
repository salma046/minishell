/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:12 by salaoui           #+#    #+#             */
/*   Updated: 2024/10/13 11:31:57 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

// search_errors(void)
// in here first check if the first token is a pipe
// check if the last token is a pipe | all_redires
// check if there are two followed tokens and both are pipes

void free_redir_list(t_redir *redir)
{
    t_redir *current;
    t_redir *next;

    current = redir;
    while (current != NULL)
    {
        next = current->next;    // Save the next redir node
        free(current->file);     // Free the file string
        free(current);           // Free the current redir structure
        current = next;          // Move to the next redir node
    }
}


void free_node(t_node *node)
{
    int i = 0;

    // Free each command in the cmd array
    if (node->cmd)
    {
        while (node->cmd[i])
        {
            free(node->cmd[i]);
            i++;
        }
        free(node->cmd);  // Free the array itself
    }

    // Free the redirections list
    if (node->redir)
        free_redir_list(node->redir);

    // Finally, free the node itself
    free(node);
}


void free_node_list(t_node *node_list)
{
    t_node *current;
    t_node *next;

    current = node_list;
    while (current != NULL)
    {
        next = current->next_node;  // Save the next node
        free_node(current);         // Free the current node
        current = next;             // Move to the next node
    }
}

int	main(int ac, char *av[], char **env)
{
	g_minishell.envirement = env;
	t_node *tmp_node;
	int i;
	int j;

	while (1)
	{
		g_minishell.command = readline("Minishell~$ ");
		if (!g_minishell.command)
		{
			printf("Quiting minishell!\n");
			exit(1);
		}
		add_history(g_minishell.command);
		g_minishell.tokens = ft_tokenize(g_minishell);
		if (!g_minishell.tokens)
			continue ;
		g_minishell.tokens = rmp_dollar(g_minishell.tokens); // in progress // Done
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		g_minishell.nodes = mk_nodes(g_minishell.tokens);
		tmp_node = g_minishell.nodes;
		while (tmp_node)
		{
			j = 0;
			i = 0;
			printf("----------------------------------------------------------\n");
			while(tmp_node->cmd[j])
			{
				printf("the node \033[32m%d\033[0m cmds n* %d is :\033[32m %s\033[0m\n",
				i, j, tmp_node->cmd[j]);
				j++;
			}
			while(tmp_node->redir)
			{
				printf("the redir file name is: %s\n",
					tmp_node->redir->file);
				printf("the redir type is: %d\n",
					tmp_node->redir->red_type);
				tmp_node->redir = tmp_node->redir->next;
			}
			printf("----------------------------------------------------------\n");
			tmp_node = tmp_node->next_node;
			i++;
		}
		free_node_list(g_minishell.nodes);
	}
}
