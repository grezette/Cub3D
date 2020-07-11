/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 20:03:36 by grezette          #+#    #+#             */
/*   Updated: 2020/07/11 22:52:29 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	void	ft_init_raytracer(t_cub *cub, int x)
{
	cub->cameraX = 2 * x / (double)cub->reso.x - 1;
	cub->rayDir.x = cub->dir.x + cub->plane.x * cub->cameraX;
	cub->rayDir.y = cub->dir.y + cub->plane.y * cub->cameraX;
	cub->w_map.x = (int)cub->pos.x;
	cub->w_map.y = (int)cub->pos.y;
	cub->deltaDist.x = (cub->rayDir.x < 0) ? 1 / cub->rayDir.x * -1 : \
					1 / cub->rayDir.x;
	cub->deltaDist.y = (cub->rayDir.y < 0) ? 1 / cub->rayDir.y * -1 : \
					1 / cub->rayDir.y;
	cub->hit = 0;
}

static	void	ft_if_raydir(t_cub *cub)
{
	if (cub->rayDir.x < 0)
	{
		cub->step.x = -1;
		cub->sideDist.x = (cub->w_map.x + 1.0 - cub->pos.x) * cub->deltaDist.x;
	}
	else
	{
		cub->step.x = 1;
		cub->sideDist.x = (cub->w_map.x + 1.0 - cub->pos.x) * cub->deltaDist.x;
	}
	if (cub->rayDir.y < 0)
	{
		cub->step.y = -1;
		cub->sideDist.y = (cub->w_map.y + 1.0 - cub->pos.y) * cub->deltaDist.y;
	}
	else
	{
		cub->step.y = 1;
		cub->sideDist.y = (cub->w_map.y + 1.0 - cub->pos.y) * cub->deltaDist.y;
	}
}

static	void	ft_rayt_dda(t_cub *cub)
{
	while (!cub->hit)
	{
		if (cub->sideDist.x < cub->sideDist.y)
		{
			cub->sideDist.x += cub->deltaDist.x;
			cub->w_map.x += cub->step.x;
			cub->side = 0;
		}
		else
		{
			cub->sideDist.y += cub->deltaDist.y;
			cub->w_map.y += cub->step.y;
			cub->side = 1;
		}
		if (cub->map[cub->w_map.y][cub->w_map.x] == 1)
			cub->hit = 1;
	}
	/*C'est possible que se ternaire soit fucked up mdr*/
	cub->perpWallDist = (cub->side == 0) ? (cub->w_map.x - cub->pos.x + \
			(1 - cub->step.x) / 2) / cub->rayDir.x : (cub->w_map.y - \
				cub->pos.y + (1 - cub->step.y) / 2) / cub->rayDir.y;
}

static	void	ft_rayt_height(t_cub *cub)
{
	cub->lineHeight = (int)(cub->reso.y / cub->perpWallDist);
	cub->drawStart = -cub->lineHeight / 2 + cub->reso.y / 2;
	cub->drawStart = (cub->drawStart < 0) ? 0 : cub->drawStart;
	cub->drawEnd = cub->lineHeight / 2 + cub->reso.y / 2;
	if (cub->drawEnd >= cub->reso.y)
		cub->drawEnd = cub->reso.y - 1;
}

void			ft_raytracer(t_cub *cub)
{
	int	x;

	x = -1;
	while (++x < cub->reso.x)
	{
		ft_init_raytracer(cub, x);
		ft_if_raydir(cub);
		ft_rayt_dda(cub);
		ft_rayt_height(cub);
		cub->drawStart--;
		while (++cub->drawStart < cub->drawEnd)
			cub->data[4 * x + 4 * cub->reso.x * cub->drawStart] = (char)255;
	}
	mlx_loop(cub->mlx_ptr);
}
