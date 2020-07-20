/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:53:48 by grezette          #+#    #+#             */
/*   Updated: 2020/07/20 16:59:30 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_print_parsing(t_cub *cub)
{
	int i;

	i = -1;
	printf("R %d %d\n", cub->reso.x, cub->reso.y);
	printf("NO %s\n", cub->n_txtr);
	printf("SO %s\n", cub->s_txtr);
	printf("WE %s\n", cub->w_txtr);
	printf("EA %s\n\n", cub->e_txtr);
	printf("S %s\n", cub->spt_txtr);
	printf("F %d,%d,%d\n", cub->floor.red, cub->floor.green, cub->floor.blue);
	printf("C %d,%d,%d\n", cub->ceiling.red, cub->ceiling.green,
			cub->ceiling.blue);
	while (cub->map[++i])
		printf("%s\n", cub->map[i]);
}
