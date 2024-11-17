#include "minishell.h" // ur  header

void ft_output(int ac, char *av[])
{
	if (ac != 4) // I need to add the checker of av[2] == '>'
	{
		printf("I need the file name please :)");
		return ;
	}
	int fd = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("fd");
		exit(EXIT_FAILURE);
	}
	int original_stdout = dup(STDOUT_FILENO);

	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("NO SUCH FILE");
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (execlp(av[1], av[1], NULL) == -1)
	{
		perror("execlp");
		close(fd);
		close (original_stdout);
		return ;
	}

	if (dup2(original_stdout, STDOUT_FILENO) == -1 )
	{
		perror("dup2");
		close(original_stdout);
		close (fd);
		exit(EXIT_FAILURE);
	}
	close (fd);
	close  (original_stdout);
}
// int main(int ac, char *av[])
// {
// 	ft_output(ac, av);
// 	return 0;
// }

