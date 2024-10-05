/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:24:40 by salaoui           #+#    #+#             */
/*   Updated: 2024/10/01 13:32:28 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
