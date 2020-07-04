/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:35:14 by grezette          #+#    #+#             */
/*   Updated: 2020/02/16 16:02:00 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	int		i;
	float	at;
	float	of;
	int		minus;
	int		aftr;

	aftr = 1;
	at = 0;
	of = 0;
	minus = 1;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			minus = -1;
	while (ft_isdigit(str[i]))
		at = at * 10 + str[i++] - '0';
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		of = of * 10 + str[i++] - '0';
		aftr *= 10;
	}
	return ((at + of / aftr) * minus);
}
