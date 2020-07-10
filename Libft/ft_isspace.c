#include "libft.h"

int		ft_isspace(int c)
{
	if (c == '\f' || c == '\t' || c == ' ' ||
			c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}
