#include "../minishell.h"



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
void check_missing_env_var_expo(t_env **env)
{
    char *current_directory;
    char *tmp_path;
    // t_env *tmp;

    if (ft_getenv("PATH", *env) == NULL)
        add_env_node(env, make_new_expor("PATH=/home/saait-si/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"));
    if (ft_getenv("SHLVL", *env) == NULL)
        add_env_node(env, make_new_expor("SHLVL=1"));
    if (ft_getenv("PWD", *env) == NULL)
    {
        current_directory = getcwd(NULL, 0);
        if (current_directory)
        {
        tmp_path = ft_strjoin("PWD=", current_directory);
        if (tmp_path)
            add_env_node(env, make_new_expor(tmp_path));
        free(current_directory);
        free(tmp_path);
        }
    }
    // if (ft_getenv("OLDPWD", *env) == NULL)
    // {
    //     tmp = malloc(sizeof(t_env));
    //     if (!tmp)
    //         return ;
    //     tmp->key = ft_strdup("OLDPWD");
    //     if (!tmp->key)
    //     {
    //         free(tmp);
    //         return ;
    //     }
    //     tmp->value = NULL;
    //     tmp->next = NULL;
    //     add_env_node(env, tmp);
    // }
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

