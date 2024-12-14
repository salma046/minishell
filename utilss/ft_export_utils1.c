#include "../minishell.h"

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
void add_env_node(t_env **env, t_env *new_node)
{
    t_env *tmp;

    if (!new_node)
        return;
    if (!*env)
    {
        *env = new_node;
        return;
    }
    tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void check_missing_env_var(t_env **env)
{
    char *current_directory;
    char *tmp_path;

    if (ft_getenv("PATH", *env) == NULL)
        add_env_node(env, make_new_node("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"));
    if (ft_getenv("SHLVL", *env) == NULL)
        add_env_node(env, make_new_node("SHLVL=1"));
    if (ft_getenv("PWD", *env) == NULL)
    {
        current_directory = getcwd(NULL, 0);
        if (current_directory)
        {
        tmp_path = ft_strjoin("PWD=", current_directory);
        if (tmp_path)
            add_env_node(env, make_new_node(tmp_path));
        free(current_directory);
        free(tmp_path);
        }
    }
    if (ft_getenv("_", *env) == NULL)
        add_env_node(env, make_new_node("_=minishell"));
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
    check_missing_env_var(&head);
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
