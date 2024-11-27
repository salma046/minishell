#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
	{
		return (-1);
	}
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_sigint(int x)
{
	static int	i;

	(void)x;
	if (i == 0)
		write(1, "~$\n~$", 6);
	else
		write(1, "~$^C \n~$", 8);
}

void	*mk_env_4expo(char **envir)
{
	int		i;
	t_env	*head;
	t_env	*last_node;
	t_env	*cmd_env;
	char	*equal_env;

	i = 0;
	head = NULL;
	last_node = NULL;
	while (envir[i] != NULL)
	{
		cmd_env = (t_env *)malloc(sizeof(t_env));
		if (!cmd_env)
			exit(1);
		equal_env = ft_strchr(envir[i], '=');
		if (equal_env != NULL)
		{
			cmd_env->key = ft_strndup(envir[i], equal_env - envir[i]);
			cmd_env->value = put_quot2_value(ft_strndup(equal_env + 1, ft_strlen(envir[i] + 1)));
			cmd_env->next = NULL;
		}
		if (last_node == NULL)
			head = cmd_env;
		else
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	return (head);
}

void	*mk_env(char **envir)
{
	int		i;
	t_env	*head;
	t_env	*last_node;
	t_env	*cmd_env;
	char	*equal_env;

	i = 0;
	head = NULL;
	last_node = NULL;
	while (envir[i] != NULL)
	{
		cmd_env = (t_env *)malloc(sizeof(t_env));
		if (!cmd_env)
			exit(1);
		equal_env = ft_strchr(envir[i], '=');
		if (equal_env != NULL)
		{
			cmd_env->key = ft_strndup(envir[i], equal_env - envir[i]);
			cmd_env->value = ft_strndup(equal_env + 1, ft_strlen(envir[i] + 1));
			cmd_env->next = NULL;
		}
		if (last_node == NULL)
			head = cmd_env;
		else
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	return (head);
}
