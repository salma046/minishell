/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:12 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/15 21:37:40 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

// search_errors(void)
// in here first check if the first token is a pipe
// check if the last token is a pipe | all_redires
// check if there are two followed tokens and both are pipes

char	*remp_with_null(char *str)
{
	int i = 0;
	int j = 0;
	char *word;

	while (str[i] != '\0')
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] == '$')
		{
			printf("hello world i is: %d\n", i);
			// exit(0);
			i++;
			j++;
		}
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
		{
			printf("hello world i is: %d\n", i);
			i++;
			j++;
		}
		if (str[i] == '\0')
		{
			printf("the result of str is: %d i is: %d and j is: %d\n", (i - j + 1), i, j);
			/////!!!!! make a function that returns from the beginning of the str intil i and other ft that returns from i intil the end 
			/////!!!!! and last ft that has the env var;
			////!!!!! last step is to join
			// return (new_str(first_ft, second_ft, env_var));
		}
	}
	word = malloc(sizeof(char) * i - j + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			word[j++] = str[i++];
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
		{
			i++;
		}
	}
	printf("the new word is: %s\n", word);
	return(word);
}

char	*remplace_doll_str(char	*data, int i, char *env_var)
{
	if (env_var == NULL)
	{
		return (remp_with_null(data));
	}
	// char *word = (char *)malloc(i + ft_strlen(env_var) + );
	printf("::::::::%s\n", data);
	printf("::::::::%s\n", env_var);
	return (data);
}

char	*get_env_var(char *str, int i)
{
	char *env_var;
	i++;
	int j = i;
	int temp = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
		i++;
	env_var = (char *)malloc(i - j + 1);
	while (j < i)
		env_var[temp++] = str[j++];
	env_var[temp] = '\0';
	// printf("your word is: %s\n", env_var);
	
	if (getenv(env_var) == NULL)
	{
		free(env_var);
		return (NULL);
	}
	else
		return (getenv(env_var));
	
}

t_token	*rmp_dollar(t_token *tokens)
{
	int i;
	int count_quotes;
	char *env_var;
	t_token	*temp_tokens;

	temp_tokens = tokens;

	while (temp_tokens)
	{
		i = 0;
		env_var = NULL;
		if (temp_tokens->data_type == 0)
		{
			while (temp_tokens->data[i])
			{
				if (temp_tokens->data[i] == '\'')
				{
					i++;
					while(temp_tokens->data[i] && temp_tokens->data[i] != '\'')
						i++;
					if (temp_tokens->data[i] == '\'')
						i++;
				}
				else if (temp_tokens->data[i] == '$')
				{
					env_var = get_env_var(temp_tokens->data, i);
					if (env_var)
						printf("------>%s\n", env_var);
					else
						printf("------>null\n");
					temp_tokens->data = remplace_doll_str(temp_tokens->data, i, env_var);
					i++;   //!!!! IMPORTANT THIS LINE SHOULD BECOME 'i = 0;' AFTER MODIFYING THE TOKEN EACH TIME ONE TIME IT WILL NO MORE HAS THAT DOLLAR IN IT !!!!//
				}
				else if (temp_tokens->data[i])
					i++;
			}
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (tokens);
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
		g_minishell.tokens = rmp_dollar(g_minishell.tokens); // in progress
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
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
