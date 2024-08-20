#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void	handle_int_sig(int a, siginfo_t *info, void *av)
{
	(void)av;
	if (a == SIGINT)
	{
		printf("\n");
		rl_on_new_line();  // Move the cursor to the beginning of the line
		rl_redisplay();
	}
}

void ignore_sig(int a)
{


}

int	split_str(const char *str)
{
	int	i;
	int j;
	int l;
	int words_counter;
	// char *word = malloc(sizeof(char) * 6);  //// HELLO PAY ATTENTION TO THE ALLOCATION IF THE STRING WAS NOT ALLOCATED IT WILL NOT BE SAVED.

	i = 0;
	j = 0;
	l = 0;
	words_counter = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (l == 0 && str[i] == '|')
		{
			printf("Some syntax error\n");
			return (0);
		}
		l = 1;
		while (str[i] != '|' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
		{
			printf(" i is : %d\n", i);
			// exit (0);
			word[j++] = str[i++];
		}
		word[j] = '\0';
		printf("---%s\n", word); // IF YOU WANT THIS TO NOT SIGFAULT YOU JUST SHOULD UNCOMMENT THE ALLOCATION PART!!! 
		exit(0);
	}
	return (1);
}

int main()
{
	struct sigaction sig;

	sig.sa_sigaction = handle_int_sig;
	while(1)
	{
		if (sigaction(SIGINT, &sig, NULL) == -1)
			exit(write(2, "Error\n", 6));
		signal(SIGTSTP, ignore_sig);
		char *str = readline ("Minishell $");
		if (str == NULL || strcmp(str, "exit") == 0)
		{
			printf("exit\n");
			free(str);
			break;
		}
		// First part is to make a good array of strings comming from prompt string this s
		// string will be splited by the spaces-pipes-here-doc-redirections that's all
		// second part : --Is whenever found a pipe gonna check every thing before it after it 
		// than do the same process for the here-doc and every thing
		add_history(str);
		int a = split_str(str);
		free(str);
	}
}


int grep_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	return (0);
}