#include "../minishell.h"

int	ft_check_builtins(char *command)
{
	if (!command || command[0] == '\0')
		return (-1);
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	return (0);
}
void	execute_the_builtin(t_minishell *data, t_node *nodes, char **cmd)
{
	if (!ft_strcmp(cmd[0], "env"))
	{
		ft_env(nodes, &data);
	}
	if (!ft_strcmp(cmd[0] , "unset"))
	{
		ft_unset(data);
	}
	if (!ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(nodes);
	}
	if (!ft_strcmp(cmd[0], "cd"))
	{
		ft_cd(data);
	}
	if (!ft_strcmp(cmd[0], "pwd"))
	{
		ft_pwd(nodes);
	}
	if (!ft_strcmp(cmd[0], "exit"))
	{
		ft_exit(data);
	}
	if (!ft_strcmp(cmd[0], "export"))
	{
		ft_export(data, data->export_env, data->envir);
	}
}


void	check_command(t_minishell *data, t_node *node)
{
	int	pid;

	if (data->count_pips == 1)
		execute_the_builtin(data, node, node->cmd);
	else if (data->count_pips > 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork");
			return ;
		}
		else if (pid == 0)
		{
			execute_the_builtin(data, node, node->cmd);
			exit(0); //Child proccess;;; // save the return exit status to be put on the $?
		}
	}
	// and then in the end save the exit staus here 
	// execute_the_builtin; // Already done
}
