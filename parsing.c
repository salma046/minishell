
#include "minishell.h"

t_token	*parsing(t_minishell g_minishell)
{
	t_token	*tokens;

	tokens = g_minishell.tokens;
	if (tokens->data_type == 1)
	{
		printf("syntax error\n");
		g_minishell.tokens = NULL;
		return (g_minishell.tokens);
	}
	while (tokens)
	{
		if (tokens->next_token == NULL && tokens->data_type != 0)
		{
			printf("syntax error\n");
			g_minishell.tokens = NULL;
			return (g_minishell.tokens);
		}
		if ((tokens->data_type == 2 || tokens->data_type == 3 || tokens->data_type == 4 || tokens->data_type == 5) && tokens->next_token->data_type != 0)
		{
			printf("syntax error\n");
			g_minishell.tokens = NULL;
			return (g_minishell.tokens);
		}
		if (tokens->data_type == 1)
		{
			if (tokens->next_token != NULL && tokens->next_token->data_type == 1)
			{
				printf("syntax error\n");
				g_minishell.tokens = NULL;
				return (g_minishell.tokens);
			}
		}
		tokens = tokens->next_token;
	}
    return (g_minishell.tokens);
}
   
// int ft_input(t_token *tokens)
// {
//     t_token *current = tokens;
//     int fd;
//     char *filename = NULL;
//     int original_stdin;

//     // Save original stdin
//     original_stdin = dup(STDIN_FILENO);
//     if (original_stdin == -1)
//     {
//         perror("Failed to duplicate stdin");
//         return -1;
//     }

//     // Find input redirection token
//     while (current)
//     {
//         if (current->data_type == INP_REDIR)
//         {
//             // Validate filename
//             if (!current->next_token || !current->next_token->data)
//             {
//                 close(original_stdin);
//                 return (printf("syntax error near unexpected token '<'\n"));
//             }

//             filename = current->next_token->data;
//             break;
//         }
//         current = current->next_token;
//     }

//     // If no filename found, restore stdin and return
//     if (!filename)
//     {
//         close(original_stdin);
//         return 0;
//     }

//     // Open file
//     fd = open(filename, O_RDONLY);
//     if (fd < 0)
//     {
//         close(original_stdin);
//         return (printf("Error: Cannot open file %s\n", filename));
//     }

//     // Redirect input
//     if (dup2(fd, STDIN_FILENO) == -1)
//     {
//         perror("Error redirecting input");
//         close(fd);
//         dup2(original_stdin, STDIN_FILENO);
//         close(original_stdin);
//         return -1;
//     }
//     // Close the file descriptor
//     close(fd);

//     return 0;
// }