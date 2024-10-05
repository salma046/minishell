/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:12 by salaoui           #+#    #+#             */
/*   Updated: 2024/10/01 14:21:06 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

// search_errors(void)
// in here first check if the first token is a pipe
// check if the last token is a pipe | all_redires
// check if there are two followed tokens and both are pipes

void	ft_redi_add_back(t_redir **redirections, t_redir *new_redir)
{
	t_redir *arrs;

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

void	fill_redi(enum e_token_type token_t, char *red_file, t_redir **redirections)
{
	t_redir *new_redir;

	new_redir = malloc(sizeof(t_redir));
	if(!new_redir)
		return ;
	new_redir->red_type = token_t;
	new_redir->file = ft_strdup(red_file);
	new_redir->next = NULL;
	ft_redi_add_back(redirections, new_redir);
}

void	ft_node_add_back(t_node **node_list, t_node *new_node)
{
	t_node *arrs;

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

int cmd_count(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens && tokens->data_type != PIPE)
	{
		if (tokens->data_type == OUT_REDIR || tokens->data_type == APPEND ||
            tokens->data_type == INP_REDIR || tokens->data_type == HER_DOC)
			tokens = tokens->next_token;
		else
		{
			i++;
		}
		tokens = tokens->next_token;
	}
	return (i);
}

void	fill_node(t_token *temp_tokens, t_node **node_list)
{
	t_node *node;
	t_redir *redirections;
	t_token *tokens;
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
		if (tokens->data_type == OUT_REDIR || tokens->data_type == APPEND ||
            tokens->data_type == INP_REDIR || tokens->data_type == HER_DOC)
		{
			fill_redi(tokens->data_type, tokens->next_token->data, &redirections);	
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

void	fill_commands(t_node **node_list, t_token *tokens, int num_cmds)
{
    int cmd_idx = 0;
    int arg_idx = 0;

    while (tokens) {
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
	int		cmd_count;
	int		i;

	nodes = NULL;
	i = 0;
	// count pipes in one command
	cmd_count = count_pipe(tokens);
	
	fill_commands(&nodes, tokens, cmd_count);
	return (nodes);
}

int	main(int ac, char *av[], char **env)
{
	g_minishell.envirement = env;
	int i;
	int j;

	while (1)
	{
		// doing signals -sigint & -sigquit
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
		while (g_minishell.nodes)
		{
			j = 0;
			i = 0;
			printf("----------------------------------------------------------\n");
			while(g_minishell.nodes->cmd[j])
			{
				printf("the node \033[32m%d\033[0m cmds n* %d is :\033[32m %s\033[0m\n",
				i, j, g_minishell.nodes->cmd[j]);
				j++;
			}
			while(g_minishell.nodes->redir)
			{
				printf("the redir file name is: %s\n",
					g_minishell.nodes->redir->file);
				printf("the redir type is: %d\n",
					g_minishell.nodes->redir->red_type);
				g_minishell.nodes->redir = g_minishell.nodes->redir->next;
			}
			printf("----------------------------------------------------------\n");
			g_minishell.nodes = g_minishell.nodes->next_node;
			i++;
		}
	}
}
