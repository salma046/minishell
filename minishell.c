/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:12 by salaoui           #+#    #+#             */
/*   Updated: 2024/08/31 12:05:04 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell minishell;

void	ft_skipp_spaces(char **line)
{
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == 'v' || **line == '\r')
		(*line)++;
}

void	token_new_word(char *word, enum e_token_type token_t, t_token **tokens_list)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token *));
	new_token->data = word;
	new_token->data_type = token_t;
	new_token->next_token = NULL;

	ft_lstadd_back(tokens_list, new_token);
}

void token_new_sep(enum e_token_type token_t, t_token **tokens_list)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token *));
	new_token->data = NULL;
	new_token->data_type = token_t;
	new_token->next_token = NULL;

	ft_lstadd_back(tokens_list, new_token);
}

void	ft_put_token(char **line, enum e_token_type token_t, t_token **tokens_list)
{
	if (token_t == APPEND)
	{
		token_new_sep(APPEND, tokens_list);
		(*line)++;
	}
    else if (token_t == HER_DOC)
	{
		token_new_sep(HER_DOC, tokens_list);
		(*line)++;
	}
	else
		token_new_sep(token_t, tokens_list);
	(*line)++;
}

void	ft_put_word_token(char **line, enum e_token_type token_t, t_token **tokens_list)
{
	char *word;

	word = *line;
	while (**line != '\0' && strncmp(*line, "|", 1) != 0 && strncmp(*line, "<", 1) != 0
	&& strncmp(*line, ">", 1) != 0 &&strncmp(*line, "<<", 1) != 0
	&& strncmp(*line, ">>", 1) != 0)
		(*line)++;
	word = ft_str_until(word, **line);
	token_new_word(word, WORD, tokens_list);
	// free(word);
	
}

t_token	*ft_tokenize(void)
{
	t_token *tokens_list;
	char *line;

	tokens_list = NULL;
	line = minishell.command;
	while (*line)
	{
		ft_skipp_spaces(&line);
        if (strncmp(line, "|", 1) == 0)
	        ft_put_token(&line, PIPE, &tokens_list);
        else if (strncmp(line, ">>", 2) == 0)
            ft_put_token(&line, APPEND, &tokens_list);
        else if (strncmp(line, "<<", 2) == 0)
            ft_put_token(&line, HER_DOC, &tokens_list);
        else if (strncmp(line, ">", 1) == 0)
            ft_put_token(&line, OUT_REDIR, &tokens_list);
        else if (strncmp(line, "<", 1) == 0)
            ft_put_token(&line, INP_REDIR, &tokens_list);
        else
            ft_put_word_token(&line, WORD, &tokens_list);
	}
	return (tokens_list);
}

int	main(int ac, char *av[], char **env)
{
	minishell.envirement = env;

	while (1)
	{
		// doing signals -sigint & -sigquit
		minishell.command = readline("Minishell~$ ");
		if (!minishell.command)
		{
			// handle quit for the moment print a string ->quit;
			printf("Quiting !\n");
			exit (1);
		}
		add_history(minishell.command);
		minishell.tokens = ft_tokenize();
		while(minishell.tokens)
		{
			printf("\nthe token is the linked list is: %s\n", minishell.tokens->data);
			printf("the token type is the linked list is: %d\n", minishell.tokens->data_type);
			minishell.tokens = minishell.tokens->next_token;
		}
		exit(0);
	}
}
