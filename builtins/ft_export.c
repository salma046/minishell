#include "../minishell.h"

/// Warnign : add_struct_2_env for what ?? raha makaynax
void	search_check_add_env(t_env *expo_envir, t_env *env_envir)
{
	t_env	*to_check;

	to_check = expo_envir;
	while (to_check)
	{
		if (to_check->value == NULL)
		{
			to_check = to_check->next;
			continue ;
		}
		else if (check_key(to_check->key, env_envir) != 1)
		{
			add_struc_2_env(to_check, env_envir);
		}
		to_check = to_check->next;
	}
}

int	ft_add_to_export_arg(t_node *nodes, t_env *expo_envir, t_env *env_envir)
{
	char	**commands;

	commands = nodes->cmd;
	if (!commands || !commands[1] || !expo_envir)
		return (-1);
	commands++;
	while (*commands)
	{
		if (*commands == NULL)
		{
			commands++;
			continue ;
		}
		if (not_valid(*commands) == 1)
		{
			write(2, "bash: export: ", ft_strlen("bash: export: "));
			write(2, *commands, ft_strlen(*commands));
			write(2, "': not a valid identifier", 25);
			write(2, "\n", 1);
			return (0);
		}
		process_key(*commands, expo_envir, env_envir);
		commands++;
	}
	return (0);
}

int	ft_env_export_once(t_node *nodes, t_env *envir, int active)
{
	t_env	*head;
	t_env	*current;

	(void)nodes;
	head = envir;
	if (active == 1)
		sort_env(head);
	current = head;
	while (current)
	{
		if (current->value == NULL || !ft_strcmp(current->value, ""))
		{
			current->value = ft_strdup("");
			printf("declare -x %s%s\n", current->key, current->value);
		}
		else if (active == 1)
			printf("declare -x %s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	ft_export(t_minishell *data, t_env *expo_envir, t_env *env_envir)
{
	int		active;
	t_node	*tmp_nodes;

	tmp_nodes = data->nodes;
	if (!tmp_nodes->cmd[0] || !expo_envir)
		return (0);
	active = 1;
	if ((tmp_nodes->cmd[1] == NULL && tmp_nodes->cmd[0]))
	{
		if (!ft_strcmp(tmp_nodes->cmd[0], "export"))
			g_minishell.exit_status = ft_env_export_once(tmp_nodes, expo_envir,
					active);
	}
	else
	{
		active = 0;
		g_minishell.exit_status = ft_add_to_export_arg(tmp_nodes, expo_envir,
				env_envir);
	}
	search_check_add_env(expo_envir, env_envir);
	return (g_minishell.exit_status);
}
