/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:01:30 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/18 13:10:36 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	put_env_null_word(char *str, char *word, int *i, int *j)
{
	size_t	l;

	l = 0;
	(*i)++;
	while (check_is_num(str, *i) == 1)
		(*i)++;
	while (str[*i])
		word[(*j)++] = str[(*i)++];
	word[*j] = '\0';
	return (l);
}
