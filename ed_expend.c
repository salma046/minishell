#include "minishell.h"

t_token	*new_token_env(char *str, t_token *tokens, char *edi_env)
{
    t_token *tmp_tokens;
    t_token *tmp_tokens_next;
    int i = 0;
    int j = 0;
    char modified_part[256];

    tmp_tokens = tokens;
    tmp_tokens_next = tmp_tokens->next_token;

    while (edi_env[i] != ' ' && edi_env[i] != '\t' && edi_env[i] != '\n' && edi_env[i] != '\0')
    {
        modified_part[j] = edi_env[i];
        // printf("the edi env is: %c\n", (*edi_env)[i]);
        j++;
        i++;
    }
    modified_part[j] = '\0';
    printf("the new data is: %s\n", modified_part);
    tmp_tokens->data = remplace_doll_str(str, modified_part, 1);
    tmp_tokens = tmp_tokens->next_token;
    while (edi_env[i] != '\0')
    {
        j = 0;
        while (edi_env[i] == ' ' || edi_env[i] == '\t' || edi_env[i] == '\n')
            i++;
        while (edi_env[i] != ' ' && edi_env[i] != '\t' && edi_env[i] != '\n' && edi_env[i] != '\0')
        {
            modified_part[j] = edi_env[i];
            j++;
            i++;
        }
        modified_part[j] = '\0';
        printf("the new data is: %s\n", modified_part);
        // tmp_tokens->data = remplace_doll_str("", modified_part, 1);
        token_new_word(modified_part, WORD, &tokens);
        tmp_tokens = tmp_tokens->next_token;
    }
    if (tmp_tokens)
        tmp_tokens->next_token = tmp_tokens_next;
    else
        tmp_tokens = tmp_tokens_next;
    while (tokens)
    {
        printf("tokens the data is: %s\n", tokens->data);
        tokens = tokens->next_token;
    }
    exit(345);
    return (tokens);
}

// t_token *new_token_env(char *str, t_token *tokens, char **edi_env)
// {
//     t_token *tmp_tokens;
//     int i = 0;
//     char modified_part[256];  // Adjust size if needed
//     (void)str;

//     tmp_tokens = tokens;

//     // Extract a portion of *edi_env to modified_part
//     while ((*edi_env)[i] != 'a' && (*edi_env)[i] != '\0') {
//         modified_part[i] = (*edi_env)[i];
//         printf("the char is: %c\n", (*edi_env)[i]);
//         i++;
//     }
//     modified_part[i] = '\0';

//     printf("Modified part: %s\n", modified_part);

//     // Update edi_env to point to the remaining part
//     *edi_env = &(*edi_env)[i];

//     return tmp_tokens;
// }
