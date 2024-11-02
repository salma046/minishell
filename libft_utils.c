#include "minishell.h"
char	*ft_strncpy(char *dst, const char *src, size_t len)
{
    size_t i;

    i = 0;
    while (i < len && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    while (i < len)
    {
        dst[i] = '\0';
        i++;
    }
    return (dst);
}

int	is_space(char *line)
{
	if (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\f')
        return (1);
    return (0);
}

char *get_word(char *str, int i)
{
	int j = 0;
	char *word;
	word = (char *)malloc(i + 1);
    if (!word)
	{
        return (NULL);
	}
	while (j < i)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}


void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*arrs;

	arrs = *lst;
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (arrs->next_token != NULL)
	{
		arrs = arrs->next_token;
	}
	arrs->next_token = new;
	new->prev_token = arrs;
}

