/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 17:51:36 by grezette          #+#    #+#             */
/*   Updated: 2020/07/20 17:52:38 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_guess_orientation(t_cub *cub)
{
	if (!cub->side)
		return ((cub->raydir.x >= 0) ? 3 : 2);
	else
		return ((cub->raydir.y >= 0) ? 0 : 1);
}

void	ft_if_raydir(t_cub *cub)
{
	if (cub->raydir.x < 0)
	{
		cub->step.x = -1;
		cub->sidedist.x = (cub->pos.x - cub->w_map.x) * cub->deltadist.x;
	}
	else
	{
		cub->step.x = 1;
		cub->sidedist.x = (cub->w_map.x + 1.0 - cub->pos.x) * cub->deltadist.x;
	}
	if (cub->raydir.y < 0)
	{
		cub->step.y = -1;
		cub->sidedist.y = (cub->pos.y - cub->w_map.y) * cub->deltadist.y;
	}
	else
	{
		cub->step.y = 1;
		cub->sidedist.y = (cub->w_map.y + 1.0 - cub->pos.y) * cub->deltadist.y;
	}
}

void	ft_rayt_dda(t_cub *cub)
{
	while (!cub->hit)
	{
		if (cub->sidedist.x < cub->sidedist.y)
		{
			cub->sidedist.x += cub->deltadist.x;
			cub->w_map.x += cub->step.x;
			cub->side = 0;
		}
		else
		{
			cub->sidedist.y += cub->deltadist.y;
			cub->w_map.y += cub->step.y;
			cub->side = 1;
		}
		if (cub->map[cub->w_map.y][cub->w_map.x] == '1')
			cub->hit = 1;
	}
	cub->perpwalldist = (cub->side == 0) ? (cub->w_map.x - cub->pos.x +
			(1 - cub->step.x) / 2) / cub->raydir.x : (cub->w_map.y -
				cub->pos.y + (1 - cub->step.y) / 2) / cub->raydir.y;
}

void	ft_rayt_height(t_cub *cub)
{
	cub->lineheight = (int)(cub->reso.y / cub->perpwalldist);
	cub->drawstart = -cub->lineheight / 2 + cub->reso.y / 2;
	cub->drawstart = (cub->drawstart < 0) ? 0 : cub->drawstart;
	cub->drawend = cub->lineheight / 2 + cub->reso.y / 2;
	if (cub->drawend >= cub->reso.y)
		cub->drawend = cub->reso.y - 1;
}
