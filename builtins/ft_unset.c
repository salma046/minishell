/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:02:09 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/17 22:02:10 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node(t_env **head, char *keyToRemove)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (!ft_strcmp(keyToRemove, current->key))
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

t_env	*ft_env_unset(t_minishell *data)
{
	t_env	*tmp;
	char	*test;
	t_token	*temp_tokens;

	tmp = data->envir;
	temp_tokens = data->tokens->next_token;
	if (data->tokens->next_token == NULL)
		return (tmp);
	while (temp_tokens && temp_tokens->data_type == WORD)
	{
		test = temp_tokens->data;
		tmp = data->envir;
		while (tmp)
		{
			if (tmp->next != NULL && !ft_strcmp(test, tmp->next->key))
			{
				remove_node(&data->envir, test);
			}
			tmp = tmp->next;
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (tmp);
}

t_env	*ft_env_unset_for_export(t_minishell *data)
{
	t_env	*tmp;
	char	*test;
	t_token	*temp_tokens;

	tmp = data->export_env;
	temp_tokens = data->tokens->next_token;
	if (data->tokens->next_token == NULL)
		return (tmp);
	while (temp_tokens && temp_tokens->data_type == WORD)
	{
		test = temp_tokens->data;
		tmp = data->export_env;
		while (tmp)
		{
			if (tmp->next != NULL && !ft_strcmp(test, tmp->next->key))
			{
				remove_node(&data->export_env, test);
			}
			tmp = tmp->next;
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (tmp);
}

void	ft_unset(t_minishell *data)
{
	data->envir = ft_env_unset(data);
	data->export_env = ft_env_unset_for_export(data);
	g_minishell.exit_status = 0;
}
