/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:24:40 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/21 00:57:04 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_last_tok(char *str, t_minishell g_minishell)
{
	(void)g_minishell;
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i-1] == '\\')
	{
		printf("syntax error\n");
		return (0);
	}
	return (1);
}

t_token	*parsing(t_minishell g_minishell)
{
	t_token	*tokens;

	tokens = g_minishell.tokens;
	if (tokens->data_type == 1)
	{
		printf("syntax error\n");
		g_minishell.tokens = NULL;
		return (g_minishell.tokens);
	}
	while (tokens)
	{
		if (tokens->next_token == NULL && tokens->data_type == 0)
		{
			if (check_last_tok(tokens->data, g_minishell) == 0)
			{
				g_minishell.tokens = NULL;
				return (g_minishell.tokens);
			}
		}
		if (tokens->next_token == NULL && tokens->data_type != 0)
		{
			printf("syntax error\n");
			g_minishell.tokens = NULL;
			return (g_minishell.tokens);
		}
		if ((tokens->data_type == 2 || tokens->data_type == 3 || tokens->data_type == 4 || tokens->data_type == 5) && tokens->next_token->data_type != 0)
		{
			printf("syntax error\n");
			g_minishell.tokens = NULL;
			return (g_minishell.tokens);
		}
		if (tokens->data_type == 1)
		{
			if (tokens->next_token != NULL && tokens->next_token->data_type == 1)
			{
				printf("syntax error\n");
				g_minishell.tokens = NULL;
				return (g_minishell.tokens);
			}
		}
		tokens = tokens->next_token;
	}
    return (g_minishell.tokens);
}
