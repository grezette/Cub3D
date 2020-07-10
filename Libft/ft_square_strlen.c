#include "libft.h"

size_t	ft_square_strlen(char **str)
{
	int i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}
