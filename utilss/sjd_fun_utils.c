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

t_env	*make_new_expor(char *envir)
{
	t_env	*cmd_env;
	char	*equal_env;

	cmd_env = (t_env *)malloc(sizeof(t_env));
	if (!cmd_env)
		exit(1);
	equal_env = ft_strchr(envir, '=');
	if (equal_env != NULL)
	{
		cmd_env->key = ft_strndup(envir, equal_env - envir);
		cmd_env->value = put_quot2_value(ft_strndup(equal_env + 1,
					ft_strlen(envir + 1)));
		cmd_env->next = NULL;
	}
	return (cmd_env);
}

void	*mk_env_4expo(char **envir)
{
	int		i;
	t_env	*head;
	t_env	*last_node;
	t_env	*cmd_env;

	i = 0;
	head = NULL;
	last_node = NULL;
	while (envir[i] != NULL)
	{
		cmd_env = make_new_expor(envir[i]);
		if (last_node == NULL)
			head = cmd_env;
		else
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	return (head);
}

t_env	*make_new_node(char *envir)
{
	t_env	*cmd_env;
	char	*equal_env;

	cmd_env = (t_env *)malloc(sizeof(t_env));
	if (!cmd_env)
		exit(1);
	equal_env = ft_strchr(envir, '=');
	if (equal_env != NULL)
	{
		cmd_env->key = ft_strndup(envir, equal_env - envir);
		cmd_env->value = ft_strndup(equal_env + 1, ft_strlen(envir + 1));
		cmd_env->next = NULL;
	}
	return (cmd_env);
}

t_env	*mk_env(char **envir)
{
	int		i;
	t_env	*head;
	t_env	*last_node;
	t_env	*cmd_env;

	i = 0;
	head = NULL;
	last_node = NULL;
	while (envir[i] != NULL)
	{
		cmd_env = make_new_node(envir[i]);
		if (last_node == NULL)
			head = cmd_env;
		else
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	return (head);
}


char **mk_tenv_char(t_env *envir)
{
    t_env *tmp;
    char **arr;
    int i;
    int size = 0;

    tmp = envir;
    while (tmp)
    {
        size++;
        tmp = tmp->next;
    }
    arr = malloc((size + 1) * sizeof(char *));
    if (!arr)
        return NULL;
    tmp = envir;
    i = 0;
    while (tmp)
    {
        char *first_part = ft_strjoin(tmp->key, "=");
        if (!first_part)
        {
            free(arr);
            return NULL;
        }
        char *second_part = ft_strjoin(first_part, tmp->value);
        free(first_part);
        if (!second_part)
        {
            free(arr);
            return NULL;
        }
        arr[i++] = second_part;
        tmp = tmp->next;
    }
    arr[i] = NULL;
    return arr;
}
