/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:12 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/07 10:13:56 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

int	ft_skipp_spaces(char **line)
{
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == 'v'
		|| **line == '\r')
	{
		(*line)++;
	}
	if (**line == '\0')
		return (1);
	return (0);
}

void	token_new_word(char *word, enum e_token_type token_t,
		t_token **tokens_list)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->data = word;
	new_token->data_type = token_t;
	new_token->next_token = NULL;
	ft_lstadd_back(tokens_list, new_token);
}

void	token_new_sep(enum e_token_type token_t, t_token **tokens_list)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->data = NULL;
	new_token->data_type = token_t;
	new_token->next_token = NULL;
	ft_lstadd_back(tokens_list, new_token);
}

int	check_spaces(char *str)
{
	int i;

	i = 0;
	i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == 'v'
		|| str[i] == '\r')
		i++;
	if (!str[i])
	{
		printf("syntax error\n");
		return (0);
	}
	return (1);
}

int	ft_put_token(char **line, enum e_token_type token_t,
		t_token **tokens_list)
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
	if (token_t == PIPE)
	{
		char *word = *line;
		if (check_spaces(word) == 0)
			return (1);
	}
	(*line)++;
	return (0);
}

int	find_quote(char c, char **line)
{
	(*line)++;
	while (**line != '\0' && ft_strncmp(*line, &c, 1) != 0)
		(*line)++;
	if (**line == c)
		return (1);
	return (0);
}

void	ft_put_word_token(char **line, enum e_token_type token_t,
		t_token **tokens_list)
{
	char	*word;
	char	quote;

	word = *line;
	while (**line != '\0' && ft_strncmp(*line, "|", 1) != 0 && ft_strncmp(*line,
			"<", 1) != 0 && ft_strncmp(*line, ">", 1) != 0 && ft_strncmp(*line,
			"<<", 1) != 0 && ft_strncmp(*line, ">>", 1) != 0)
	{
		if (**line == '"' || **line == '\'')
		{
			quote = **line;
			if (find_quote(**line, line) == 0)
			{
				printf("syntax error missing %c\n", quote);
				return ;
			}
		}
		(*line)++;
	}
	word = ft_str_until(word, **line);
	token_new_word(word, WORD, tokens_list);
	// free(word);
}

t_token	*double_sep_token(t_token **tokens_list)
{
	t_token	*tokens = *tokens_list;

	while (tokens)
	{
		if(tokens->data_type != 0 && (tokens->next_token != NULL && tokens->next_token->data == 0))
		{
			printf("syntax error\n");
			tokens = NULL;
			return (tokens);	
		}
		tokens = tokens->next_token;
	}
	return(*tokens_list);
}

t_token	*ft_tokenize(void)
{
	t_token	*tokens_list;
	char	*line;
	int		res;

	tokens_list = NULL;
	res = 0;
	line = g_minishell.command;
	
	if (ft_strncmp(line, ">>", 2) == 0 || ft_strncmp(line, "<<", 2) == 0 || ft_strncmp(line, ">", 1) == 0 || ft_strncmp(line, "<", 1) == 0 || ft_strncmp(line, "|", 1) == 0)
	{
		if (ft_strncmp(line, "|", 1) == 0)
		{
			printf("syntax error\n");
			return (tokens_list);
		}
		if (ft_strncmp(line, ">>", 2) == 0 || ft_strncmp(line, "<<", 2) == 0)
			line++;
		line++;
		if (ft_skipp_spaces(&line) == 1)
		{
			printf("syntax error\n");
			return (tokens_list);
		}
		else
			line = g_minishell.command;
	}
	while (*line)
	{
		// printf("the line is: %s\n", line);
		if (ft_skipp_spaces(&line) == 1)
			return (tokens_list);
		if (ft_strncmp(line, "|", 1) == 0)
		{
			res = ft_put_token(&line, PIPE, &tokens_list);
			if (res != 0)
				return (NULL);
		}
		else if (ft_strncmp(line, ">>", 2) == 0)
			res = ft_put_token(&line, APPEND, &tokens_list);
		else if (ft_strncmp(line, "<<", 2) == 0)
			res = ft_put_token(&line, HER_DOC, &tokens_list);
		else if (ft_strncmp(line, ">", 1) == 0)
			res = ft_put_token(&line, OUT_REDIR, &tokens_list);
		else if (ft_strncmp(line, "<", 1) == 0)
			res = ft_put_token(&line, INP_REDIR, &tokens_list);
		else
			ft_put_word_token(&line, WORD, &tokens_list);
	}
	return(double_sep_token(&tokens_list));
	return (tokens_list);
}

int	check_last_tok(char *str)
{
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

void	search_errors(void)
{
	t_token	*tokens;

	tokens = g_minishell.tokens;
	while (tokens)
	{
		if (tokens->next_token == NULL && tokens->data_type == 0)
		{
			if (check_last_tok(tokens->data) == 0)
				return ;
		}
		if (tokens->data_type == 1)
		{
			if (tokens->next_token->data_type != 0)
			{
				printf("syntax error\n");
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
		g_minishell.tokens = ft_tokenize();
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
