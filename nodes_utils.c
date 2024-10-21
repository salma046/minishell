/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:26 by salaoui           #+#    #+#             */
/*   Updated: 2024/10/12 11:42:45 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_count(t_token *tokens)
{
	int i;

	i = 0;
	while (tokens && tokens->data_type != PIPE)
	{
		if (tokens->data_type == OUT_REDIR || tokens->data_type == APPEND ||
            tokens->data_type == INP_REDIR || tokens->data_type == HER_DOC)
			tokens = tokens->next_token;
		else
		{
			i++;
		}
		tokens = tokens->next_token;
	}
	return (i);
}

int count_pipe(t_token *tokens)
{
	t_token	*temp_tokens;
	int		count;

	temp_tokens = tokens;
    count = 0;
    while (temp_tokens)
	{
		if (temp_tokens->data_type == 1)
            count++;
        temp_tokens = temp_tokens->next_token;
    }
    count++;
    return (count);
}
