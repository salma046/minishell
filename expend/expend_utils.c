/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:36:53 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/18 00:11:06 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remp_with_edi_value(char *str, char *env_var);
int		get_l(char *str, char *env_var);

char	*token_edi_env(char *str, char *env_var, t_token **to_list)
{
	int		i;
	char	*last_word;
	char	*modif_part;
	char	*command_rest;
	char	*middle_part;

	i = 0;
	modif_part = fill_first_part(env_var, &i);
	command_rest = after_dol_word(str, get_l(str, env_var), ft_strlen(str));
	token_new_edi_word(remp_with_edi_value(str, modif_part), WORD, to_list);
	free(modif_part);
	while (env_var[i] != '\0')
	{
		middle_part = fill_middle_part(env_var, &i);
		if (env_var[i] != '\0')
			token_new_edi_word(middle_part, WORD, to_list);
		else
		{
			last_word = ft_strjoin(middle_part, command_rest);
			free(middle_part);
		}
	}
	free(str);
	free(command_rest);
	return (last_word);
}

int	get_l2(char *str, int *i, char *env_var)
{
	size_t	l;

	l = 0;
	(*i)++;
	while (check_is_num(str, *i) == 1)
		(*i)++;
	while (l < ft_strlen(env_var))
		l++;
	l = (*i);
	while (str[*i])
		(*i)++;
	return (l);
}

int	get_l(char *str, char *env_var)
{
	int		i;
	size_t	l;

	i = 0;
	while (str[i])
	{
		while (str[i] == '\'')
			skip_quo(str, &i, '\'');
		if (str[i] == '"')
			skip_double_quo(str, 0, &i);
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$'
			&& is_not_valid_expend(str, i) == 1)
			i++;
		if (str[i] != '\'' && str[i] != '"' && str[i] != '$' && str[i
				+ 1] == '$')
			i++;
		if (str[i] == '$' && str[i + 1] == '$')
			skip_double_signs(str, &i);
		if (valid_word(str, i) == 1)
			l = get_l2(str, &i, env_var);
		else if (str[i] && str[i] != '$' && str[i - 1] != '$' && str[i] != '"'
			&& str[i] != '\'')
			i++;
	}
	return (l);
}

char	*remp_with_edi_value(char *str, char *env_var)
{
	t_my_struc	norm;

	norm.word = allocate_4_nword(str, env_var);
	norm.i = 0;
	norm.j = 0;
	while (str[norm.i])
	{
		fill_word_sgl_quot(norm.word, str, &norm.i, &norm.j);
		if (str[norm.i] != '\'' && str[norm.i] != '"'
			&& str[norm.i] != '$' && str[norm.i
				+ 1] == '$')
			norm.word[norm.j++] = str[norm.i++];
		if (str[norm.i] == '$' && str[norm.i + 1] == '$')
			skip_double_signs(str, &norm.i);
		if (valid_word(str, norm.i) == 1)
			put_env_in_word(str, env_var, &norm);
		else if (str[norm.i] && str[norm.i] != '$'
			&& str[norm.i - 1] != '$' && str[norm.i] != '"'
			&& str[norm.i] != '\'')
			norm.i++;
	}
	return (norm.word);
}

int	check_4_space(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == ' ' || env_var[i] == '\t' || env_var[i] == '\n'
			|| env_var[i] == '\f')
			return (1);
		i++;
	}
	return (0);
}
