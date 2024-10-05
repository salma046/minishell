/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:02:08 by salaoui           #+#    #+#             */
/*   Updated: 2024/10/04 10:03:45 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (*line == ' ' || *line == '\t' || *line == '\n')
        return (1);
    return (0);
}

char *get_word(char *str, int i)
{
	int j = 0;
	char *word;
	word = (char *)malloc(i + 1);
    if (!word)
        return (NULL);
	while (j < i)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*ptr;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		ptr[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
	{
		ptr[i] = *s2;
		i++;
		s2++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
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

char	*ft_strdup(const char *src)
{
	int		l;
	char	*p1;

	l = 0;
	p1 = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (p1 == NULL)
	{
		return (NULL);
	}
	while (src[l])
	{
		p1[l] = src[l];
		l++;
	}
	p1[l] = '\0';
	return (p1);
}
