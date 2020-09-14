/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:53:15 by grezette          #+#    #+#             */
/*   Updated: 2020/08/09 17:34:34 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_is_parsing_finished(t_cub *cub)
{
	if (cub->reso.x < 0 || cub->reso.y < 0 ||
			cub->reso.x == 0 || cub->reso.y == 0)
		return (0);
	if (!cub->n_txtr || !cub->s_txtr || !cub->w_txtr || !cub->e_txtr ||
			!cub->spt_txtr)
		return (0);
	if (cub->floor.red == -1 || cub->ceiling.red == -1 ||
			cub->floor.green == -1 || cub->ceiling.green == -1 ||
			cub->floor.blue == -1 || cub->ceiling.blue == -1)
		return (0);
	return (1);
}

int		ft_is_parsing_ok(t_cub *cub)
{
	if (!ft_is_parsing_finished(cub))
		return (-1);
	if (cub->floor.red > 255 || cub->floor.green > 255 ||
			cub->floor.blue > 255 || cub->ceiling.red > 255 ||
			cub->ceiling.green > 255 || cub->ceiling.blue > 255)
		return (-1);
	return (0);
}

void	ft_pars_init(t_cub *cub)
{
	cub->reso.y = -1;
	cub->n_txtr = NULL;
	cub->s_txtr = NULL;
	cub->w_txtr = NULL;
	cub->e_txtr = NULL;
	cub->spt_txtr = NULL;
	cub->floor.red = -1;
	cub->floor.green = -1;
	cub->floor.blue = -1;
	cub->ceiling.red = -1;
	cub->ceiling.green = -1;
	cub->ceiling.blue = -1;
	cub->map = NULL;
	cub->scr.img_ptr = NULL;
	cub->scr_two.img_ptr = NULL;
	cub->txtr[0].img_ptr = NULL;
	cub->txtr[1].img_ptr = NULL;
	cub->txtr[2].img_ptr = NULL;
	cub->txtr[3].img_ptr = NULL;
	cub->spt_img.img_ptr = NULL;
	cub->win_ptr = NULL;
	cub->z_buffer = NULL;
	cub->sprt = NULL;
	cub->sprt_order = NULL;
	cub->sprt_dist = NULL;
}
