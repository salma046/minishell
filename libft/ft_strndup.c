#include "libft.h"

char	*ft_strndup(char *str, int j)
{
	int i;
	char *dup = malloc(sizeof(char *) * (j + 1));
	if (!dup)
		return (0);
	i = 0;
	while (str[i] && i < j)
	{
		dup[i] = str[i];
		i++;
		j++;
	}
	dup[i] = '\0';
	return (dup);
}