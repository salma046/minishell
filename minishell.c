#include "minishell.h"

t_minishell	g_minishell;

// search_errors(void)
// in here first check if the first token is a pipe
// check if the last token is a pipe | all_redires
// check if there are two followed tokens and both are pipes

int count_dollar_lenth(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] == '$')
		{
			i++;
			j++;
		}
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*remp_with_null(char *str)
{
	int i;
	int j;
	int	word_lenth;
	char *word;

	word_lenth = count_dollar_lenth(str);
	i = ft_strlen(str);
	word = malloc(sizeof(char) * i - word_lenth + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			word[j++] = str[i++];
		if (str[i] == '$')
			i++;
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
			i++;
		while (str[i])
			word[j++] = str[i++];
	}
	word[j] = '\0';
	return(word);
}

char *after_dol_word(char *str)
{
	int i;
	int j;
	int	word_lenth;
	char *word;
	char *command_rest;

	word_lenth = count_dollar_lenth(str);
	i = ft_strlen(str);
	while (str[j] && str[j] != '$')
		j++;
	word = malloc(sizeof(char) * i - word_lenth - j + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] == '$')
			i++;
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
			i++;
		while (str[i])
			word[j++] = str[i++];
	}
	word[j] = '\0';
	return (word);
	
}

char	*remp_with_value(char *str, char *env_var)
{
	int i;
	int j;
	int l;
	int k ;
	int	word_lenth;
	char *word;
	char *hi;
	char *command_rest;

	word_lenth = count_dollar_lenth(str);
	i = ft_strlen(str);
	k = ft_strlen(env_var);
	word = malloc(sizeof(char) * i - word_lenth + k + 1);
	i = 0;
	j = 0;
	l = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			word[j++] = str[i++];
		if (str[i] == '$')
			i++;
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
			i++;
		while (l <= k)
			word[j++] = env_var[l++];
		word[j] = '\0';
		if (str[i])
			i++;
	}
	command_rest = after_dol_word(str);
	hi = ft_strjoin(word, command_rest);
	free(word);
	return (hi);
}

char	*remplace_doll_str(char	*data, char *env_var)
{
	if (env_var == NULL)
		return (remp_with_null(data));
	else 
	{
		char *word = remp_with_value(data, env_var);
		return (word);
	}
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
					temp_tokens->data = remplace_doll_str(temp_tokens->data, env_var);
					i = 0;
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
	//Argumenet
	if (ac > 1)
		return (0);
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
		g_minishell.tokens = rmp_dollar(g_minishell.tokens); // in progress //Done
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		while (g_minishell.tokens)
		{
			printf("the token is:\033[32m %s\033[0m\n",
				g_minishell.tokens->data);
			printf("the token type is:\033[0;34m %d\033[0m\n",
				g_minishell.tokens->data_type);
			ft_cd(g_minishell);
			g_minishell.tokens = g_minishell.tokens->next_token;
		}
	}
}
