#include "minishell.h"

char	*remp_with_edi_value(char *str, char *env_var);
int get_l(char *str, char *env_var);

char *token_edi_env(char *str, char *env_var, t_token **token_list)
{
    int i = 0;
    int j = 0;

    char *last_word;
    char *new_token_data;
    char modified_part[256];
    // printf("the str is :->%s\n", str);

    while (env_var[i] != ' ' && env_var[i] != '\t' && env_var[i] != '\n' && env_var[i] != '\0')
    {
        modified_part[j] = env_var[i];
        // printf("the edi env is: %c\n", (*edi_env)[i]);
        j++;
        i++;
    }
    modified_part[j] = '\0';
    // printf("the new data is: %s\n", modified_part);
    int l = get_l(str, env_var);
	char *command_rest = after_dol_word(str, l, ft_strlen(str));
    // printf("the rest is: %s\n", command_rest);
    new_token_data = remp_with_edi_value(str, modified_part);
    token_new_word(new_token_data, WORD, token_list, -1);
    while (env_var[i] != '\0')
    {
        j = 0;
        while (env_var[i] == ' ' || env_var[i] == '\t' || env_var[i] == '\n')
            i++;
        while (env_var[i] != ' ' && env_var[i] != '\t' && env_var[i] != '\n' && env_var[i] != '\0')
        {
            modified_part[j] = env_var[i];
            j++;
            i++;
        }
        modified_part[j] = '\0';
        printf("the new data is: %s\n", modified_part);
        if (env_var[i] != '\0')
        {
            printf("kslfsld;\n");
            token_new_word(modified_part, WORD, token_list, -1);
        }
        else
        {
            last_word = ft_strjoin(modified_part, command_rest);
        }
    }
    return (last_word);
}

int get_l(char *str, char *env_var)
{
    int i;
	size_t l;
	int t = 0;

	i = 0;
	l = 0;
	while (str[i])
	{
		while (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"' && t != 1)
			{
				if (str[i] == '$' && str[i + 1] == '$')
				{
					while (str[i] == '$' && str[i + 1] == '$')
						i+=2;
				}
				if (str[i] != '$')
					i++;
				else
				t = 1;
			}
			if (str[i] == '"')
				i++;
		}
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$' && is_not_valid_expend(str, i) == 1)
			i++;
		if (str[i] != '\'' && str[i] != '"' && str[i] != '$' && str[i + 1] == '$')
			i++;
		if (str[i] == '$' && str[i + 1] == '$')
		{
			while (str[i] == '$' && str[i + 1] == '$')
				i+=2;
		}
		if (str[i] && str[i] == '$' && str[i + 1] != '$' && is_not_alpanum(str[i + 1]) == 1)
		{
			i++;
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
				i++;
			while (l < ft_strlen(env_var))
				l++;
			l = i;
			while (str[i])
				i++;
		}
		else if (str[i] && str[i] != '$' && str[i - 1] != '$' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	return (l);
}

char	*remp_with_edi_value(char *str, char *env_var)
{
	int i;
	int j;
	int l;
	int k;
	int t = 0;
	int	word_lenth;
	char *word;
	// char *hi;
	// char *command_rest;

	word_lenth = count_dollar_lenth(str);
	i = ft_strlen(str);
	k = ft_strlen(env_var);
	word = malloc(sizeof(char) * i - word_lenth + k + 1);
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	l = 0;
	while (str[i])
	{
		while (str[i] == '\'')
		{
			word[j++] = str[i++];
			while (str[i] && str[i] != '\'')
				word[j++] = str[i++];
			if (str[i] == '\'')
				word[j++] = str[i++];
		}
		if (str[i] == '"')
		{
			word[j++] = str[i++];
			while (str[i] && str[i] != '"' && t != 1)
			{
				if (str[i] == '$' && str[i + 1] == '$')
				{
					while (str[i] == '$' && str[i + 1] == '$')
						i+=2;
				}
				if (str[i] != '$')
					word[j++] = str[i++];
				else
				t = 1;
			}
			if (str[i] == '"')
				word[j++] = str[i++];
		}
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$' && is_not_valid_expend(str, i) == 1)
			word[j++] = str[i++];
		if (str[i] != '\'' && str[i] != '"' && str[i] != '$' && str[i + 1] == '$')
			word[j++] = str[i++];
		if (str[i] == '$' && str[i + 1] == '$')
		{
			while (str[i] == '$' && str[i + 1] == '$')
				i+=2;
		}
		if (str[i] && str[i] == '$' && str[i + 1] != '$' && is_not_alpanum(str[i + 1]) == 1)
		{
			i++;
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
				i++;
			while (l < k)
				word[j++] = env_var[l++];
			l = i;
			while (str[i])
				i++;
			word[j] = '\0';
		}
		else if (str[i] && str[i] != '$' && str[i - 1] != '$' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	// command_rest = after_dol_word(str, l, ft_strlen(str));
	// hi = ft_strjoin(word, command_rest);
	// free(command_rest);
	// free(word);
	return (word);
}

// char	*remp_with_value(char *str, char *env_var)
// {
// 	int i;
// 	int j;
// 	int l;
// 	int k;
// 	int t = 0;
// 	int	word_lenth;
// 	char *word;
// 	char *hi;
// 	char *command_rest;

// 	word_lenth = count_dollar_lenth(str);
// 	i = ft_strlen(str);
// 	k = ft_strlen(env_var);
// 	word = malloc(sizeof(char) * i - word_lenth + k + 1);
// 	if (!word)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	l = 0;
// 	while (str[i])
// 	{
// 		while (str[i] == '\'')
// 		{
// 			word[j++] = str[i++];
// 			while (str[i] && str[i] != '\'')
// 				word[j++] = str[i++];
// 			if (str[i] == '\'')
// 				word[j++] = str[i++];
// 		}
// 		if (str[i] == '"')
// 		{
// 			word[j++] = str[i++];
// 			while (str[i] && str[i] != '"' && t != 1)
// 			{
// 				if (str[i] == '$' && str[i + 1] == '$')
// 				{
// 					while (str[i] == '$' && str[i + 1] == '$')
// 						i+=2;
// 				}
// 				if (str[i] != '$')
// 					word[j++] = str[i++];
// 				else
// 				t = 1;
// 			}
// 			if (str[i] == '"')
// 				word[j++] = str[i++];
// 		}
// 		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$' && is_not_valid_expend(str, i) == 1)
// 			word[j++] = str[i++];
// 		if (str[i] != '\'' && str[i] != '"' && str[i] != '$' && str[i + 1] == '$')
// 			word[j++] = str[i++];
// 		if (str[i] == '$' && str[i + 1] == '$')
// 		{
// 			while (str[i] == '$' && str[i + 1] == '$')
// 				i+=2;
// 		}
// 		if (str[i] && str[i] == '$' && str[i + 1] != '$' && is_not_alpanum(str[i + 1]) == 1)
// 		{
// 			i++;
// 			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == 95))
// 				i++;
// 			while (l < k)
// 				word[j++] = env_var[l++];
// 			l = i;
// 			while (str[i])
// 				i++;
// 			word[j] = '\0';
// 		}
// 		else if (str[i] && str[i] != '$' && str[i - 1] != '$' && str[i] != '"' && str[i] != '\'')
// 			i++;
// 	}
// 	command_rest = after_dol_word(str, l, ft_strlen(str));
// 	hi = ft_strjoin(word, command_rest);
// 	free(command_rest);
// 	free(word);
// 	return (hi);
// }

int check_4_space(char *env_var)
{
    int i;

    i = 0;
    // printf("hello world %s\n", env_var);
    while (env_var[i])
    {
        // printf("--%c\n", env_var[i]);
        if (env_var[i] == ' ' || env_var[i] == '\t' || env_var[i] == '\n' || env_var[i] == '\f')
            return (1);
        i++;
    }
    return (0);
}
