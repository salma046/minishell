/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:02:08 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/18 17:14:45 by salaoui          ###   ########.fr       */
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

// char	*ft_str_until(const char *str, int c)
// {
// 	char	*word;
// 	size_t	len;
	
// 	len = 0;
//     while (str[len] != (char)c && str[len] != '\0')
//     {
//         len++;
//     }
//     word = (char *)malloc(len + 1);
//     if (!word)
//         return (NULL);
//     ft_strncpy(word, str, len);
//     word[len] = '\0';
//     return (word);
// }

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

int	ft_strncmp(char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
