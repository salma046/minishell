/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:12 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/21 13:58:29 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

// search_errors(void)
// in here first check if the first token is a pipe
// check if the last token is a pipe | all_redires
// check if there are two followed tokens and both are pipes

t_token	*new_tokens(t_token *tokens)
{
	int		i;
	t_token	*temp_tokens;

	temp_tokens = tokens;
	while (temp_tokens)
	{
		if (temp_tokens->data_type == 0)
		 	;
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
		if (!g_minishell.tokens)
			continue ;
		g_minishell.tokens = rmp_dollar(g_minishell.tokens); // in progress // Done
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		g_minishell.tokens = new_tokens(g_minishell.tokens);
		while (g_minishell.tokens)
		{
			printf("the token is:\033[32m %s\033[0m\n",
				g_minishell.tokens->data);
			printf("the token type is:\033[0;34m %d\033[0m\n",
				g_minishell.tokens->data_type);
			g_minishell.tokens = g_minishell.tokens->next_token;
		}
	}
}
