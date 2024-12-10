/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 00:01:46 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/10 21:33:44 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **cmds, t_minishell *data)
{
	t_env	*tmp;

	// node = data->nodes;
	tmp = data->envir;
	// printf ("[%s]\n", node->cmd[0]);
	// printf ("[%s]\n", node->cmd[1]);
	if (tmp && cmds[1] == NULL)
	{
		while (tmp)
		{
			if (tmp->value != NULL)
			{
				printf("%s", tmp->key);
				printf("%c", '=');
				printf("%s\n", tmp->value);
			}
			tmp = tmp->next;
		}
	}
	else
		fprintf (stderr, "env: %s: No such file or directory\n", cmds[1]);
}

