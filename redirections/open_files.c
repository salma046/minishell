/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:01:30 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/18 13:12:00 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_input(char *file_name, t_node *node)
{
	node->in_file = open(file_name, O_RDONLY);
	if (node->in_file == -1)
	{
		g_minishell.exit_status = 1;
		perror("fd");
		g_minishell.exit_status = 1;
		return (-1);
	}
	return (g_minishell.exit_status = 0);
}

int	ft_output(char *file_name, t_node *node)
{
	node->out_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->out_file == -1)
	{
		g_minishell.exit_status = 1;
		perror("fd");
		g_minishell.exit_status = 1;
		return (-1);
	}
	return (g_minishell.exit_status = 0);
}

int	ft_append(char *file_name, t_node *node)
{
	node->out_file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->out_file == -1)
	{
		g_minishell.exit_status = 1;
		perror("fd");
		g_minishell.exit_status = 1;
		return (-1);
	}
	return (g_minishell.exit_status = 0);
}

void	dup2_mystd_files(int in_fd, int in_fd2)
{
	dup2(in_fd, 0);
	dup2(in_fd2, 1);
	close(in_fd);
	close(in_fd2);
}

void	skip_if_isalnum(char *tokens_word, int *i)
{
	if (tokens_word[*i] == '$')
		(*i)++;
	while (tokens_word[*i] && tokens_word[*i] != '"' && tokens_word[*i] != '\''
		&& tokens_word[*i] != '$')
		(*i)++;
}
