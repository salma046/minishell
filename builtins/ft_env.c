/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:01:36 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/18 14:37:32 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **cmds, t_minishell *data)
{
	t_env	*tmp;

	tmp = data->envir;
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
		g_minishell.exit_status = 0;
	}
	else
	{
		fprintf(stderr, "env: %s: No such file or directory\n", cmds[1]);
		g_minishell.exit_status = 127;
	}
	return (g_minishell.exit_status);
}
