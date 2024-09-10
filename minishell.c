/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:12 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/10 13:38:10 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

// t_token	*token_tokens(t_token **tokens_list)
// {
// 	t_token	*tokens = *tokens_list;

// 	while (tokens)
// 	{
// 		if(tokens->data_type != 1)
// 		{
// 			while (
				
// 			)
// 		}
// 		tokens = tokens->next_token;
// 	}
// 	return(*tokens_list);
// }

int	check_last_tok(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i-1] == '\\')
	{
		g_minishell.tokens = NULL;
		printf("syntax error\n");
		return (0);
	}
	return (1);
}

// search_errors(void)
// in here first check if the first token is a pipe
// check if the last token is a pipe | all_redires
// check if there are two followed tokens and both are pipes

int	check_pipe(t_token *tokens)
{
	if (tokens->data_type == 1)
	{
		printf("syntax error\n");
		g_minishell.tokens = NULL;
		return (1);
	}
	return (0);
}

void	search_errors(void)
{
	t_token	*tokens;

	tokens = g_minishell.tokens;
	if (check_pipe(tokens) == 1)
		return ;
	while (tokens)
	{
		if (tokens->next_token == NULL && tokens->data_type == 0)
		{
			if (check_last_tok(tokens->data) == 0)
				return ;
		}
		if (tokens->next_token == NULL && tokens->data_type != 0)
		{
			printf("syntax error\n");
			g_minishell.tokens = NULL;
			return ;
		}
		if ((tokens->data_type == 2 || tokens->data_type == 3 || tokens->data_type == 4 || tokens->data_type == 5) && tokens->next_token->data_type != 0)
		{
			printf("syntax error\n");
			g_minishell.tokens = NULL;
			return ;
		}
		if (tokens->data_type == 1)
		{
			if (tokens->next_token != NULL && tokens->next_token->data_type == 1)
			{
				printf("syntax error\n");
				g_minishell.tokens = NULL;
				return ;
			}
		}
		tokens = tokens->next_token;
	}
}

int	main(int ac, char *av[], char **env)
{
	g_minishell.envirement = env;
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
		search_errors();
		while (g_minishell.tokens)
		{
			printf("the token is: %s\n",
				g_minishell.tokens->data);
			printf("the token type is: %d\n",
				g_minishell.tokens->data_type);
			g_minishell.tokens = g_minishell.tokens->next_token;
		}
	}
}

