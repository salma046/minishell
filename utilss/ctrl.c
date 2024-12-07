#include "../minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell~$");
}