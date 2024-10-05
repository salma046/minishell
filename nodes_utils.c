/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:26 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/24 15:44:54 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
