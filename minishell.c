/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:12 by salaoui           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/21 05:00:16 by saait-si         ###   ########.fr       */
=======
/*   Updated: 2024/10/13 11:58:28 by salaoui          ###   ########.fr       */
>>>>>>> 607573b32e26a53e53cddb0823930d457f179a5a
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

void free_redir_list(t_redir *redir)
{
    t_redir *current;
    t_redir *next;

    current = redir;
    while (current != NULL)
    {
        next = current->next;
        free(current->file);
        free(current);
        current = next;
    }
}

void free_node(t_node *node)
{
    int i = 0;

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
        free_redir_list(node->redir);
	free(node);
}

void free_node_list(t_node *node_list)
{
    t_node *current;
    t_node *next;

    current = node_list;
    while (current != NULL)
    {
        next = current->next_node;
        free_node(current);
        current = next;
    }
}

int ft_start_heredoc(int fd, char *limiter)
{
	char *line;

	line = readline("heredoc>");
	while(line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& (ft_strlen(line) == ft_strlen(limiter)))
			return(close(fd), 0);
		if(ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			if (!line)
				line = ft_strdup("");
		}
		ft_putendl_fd(line, fd);
		line = readline("heredoc>");
	}
	return (0); //del this line
}

int start_heredoc(int fd, char *limiter)
{
	if (!limiter)
		return (-1);
	if (ft_start_heredoc(fd, limiter) < 0)
		return (-1);
	return (0); //del this line
}

int ft_heredoc(t_token *tokens)
{
	char *limiter;
	int fd;

	fd = open("/tmp/heredoc.txt", O_RDWR | O_CREAT | O_TRUNC | O_EXCL, 0644);
	if (fd < 0)
		return (-1);
	if (tokens->next_token->data_type == WORD)
	{
		limiter = tokens->next_token->data;
		if (start_heredoc(fd, limiter) < 0)
			return (close(fd), -1);
		else
			return (close(fd), 1);
	}
	else
		return (close(fd), -1);
	return (0);
}

int main_heredoc(t_token **tokens)
{
	t_token	*temp_tokens;

	temp_tokens = *tokens;
	while (temp_tokens)
	{
		if (temp_tokens->data_type == HER_DOC && temp_tokens->next_token && ft_heredoc(temp_token) == -1)
		{
			return (-1);
		}
		temp_tokens = temp_tokens->next_token;
	}
<<<<<<< HEAD
	node->redir = redirections;
	node->cmd[i] = NULL;
	node->next_node = NULL;
	ft_node_add_back(node_list, node);
}

void	fill_commands(t_node **node_list, t_token *tokens, int num_cmds)
{
    int cmd_idx = 0;
    int arg_idx = 0;
	(void)cmd_idx;
	(void)arg_idx;
	(void)num_cmds;
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
=======
	return (0);
>>>>>>> 607573b32e26a53e53cddb0823930d457f179a5a
}

int	main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	g_minishell.envirement = env;
	t_node *tmp_node;
	int i;
	int j;
	int p;
	while (1)
	{
<<<<<<< HEAD
		g_minishell.command = readline("~$ ");
=======
		g_minishell.command = readline("Minishell~$ ");
>>>>>>> 607573b32e26a53e53cddb0823930d457f179a5a
		if (!g_minishell.command)
		{
			printf("\n Quiting minishell!\n");
			exit(1);
		}
		add_history(g_minishell.command);
		g_minishell.tokens = ft_tokenize(g_minishell);
		if (!g_minishell.tokens)
			continue ;
		g_minishell.tokens = rmp_dollar(g_minishell.tokens);
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		if (main_heredoc(g_minishell.tokens) < 0)
			continue;
		// main3(); //execution starts here;;;;
		g_minishell.nodes = mk_nodes(g_minishell.tokens);
		tmp_node = g_minishell.nodes;
		while (tmp_node)
		{
			j = 0;
			i = 0;
<<<<<<< HEAD
			p = 1;
			printf("------------------1------------------\n");
			while(g_minishell.nodes->cmd[j])
=======
			printf("----------------------------------------------------------\n");
			while(tmp_node->cmd[j])
>>>>>>> 607573b32e26a53e53cddb0823930d457f179a5a
			{
				printf("the node \033[32m%d\033[0m cmds n* %d is :\033[32m %s\033[0m\n",
				i, j, tmp_node->cmd[j]);
				j++;
			}
<<<<<<< HEAD
			check_command(g_minishell);
			while(g_minishell.nodes->redir)
=======
			while(tmp_node->redir)
>>>>>>> 607573b32e26a53e53cddb0823930d457f179a5a
			{
				printf("the redir file name is: %s\n",
					tmp_node->redir->file);
				printf("the redir type is: %d\n",
					tmp_node->redir->red_type);
				tmp_node->redir = tmp_node->redir->next;
			}
<<<<<<< HEAD
			printf("------------------2------------------\n");
			g_minishell.nodes = g_minishell.nodes->next_node;
=======
			printf("----------------------------------------------------------\n");
			tmp_node = tmp_node->next_node;
>>>>>>> 607573b32e26a53e53cddb0823930d457f179a5a
			i++;
		}
		free_node_list(g_minishell.nodes);
	}
}
