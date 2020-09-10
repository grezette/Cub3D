#include "libft.h"

void	ft_swap(void *ptr_one, void *ptr_two)
{
	void *tmp;

	tmp = ptr_one;
	ptr_one = ptr_two;
	ptr_two = tmp;
}
