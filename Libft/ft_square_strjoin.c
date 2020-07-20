/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 17:07:40 by grezette          #+#    #+#             */
/*   Updated: 2020/07/20 17:15:33 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_square_strjoin(char **tab, char *str)
{
	char	**ret;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		if (!(ret[i] = ft_strdup(tab[i])))
			return (ft_square_free(ret));
	i = (i < 0) ? 0 : i;
	if (str)
		if (!(ret[i] = ft_strdup(str)))
			return (ft_square_free(ret));
	ret[i + 1] = NULL;
	return (ret);
}
