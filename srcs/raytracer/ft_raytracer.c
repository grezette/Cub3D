/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 20:03:36 by grezette          #+#    #+#             */
/*   Updated: 2020/07/15 15:31:29 by grezette         ###   ########.fr       */
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
		cub->sideDist.x = (cub->pos.x - cub->w_map.x) * cub->deltaDist.x;
	}
	else
	{
		cub->step.x = 1;
		cub->sideDist.x = (cub->w_map.x + 1.0 - cub->pos.x) * cub->deltaDist.x;
	}
	if (cub->rayDir.y < 0)
	{
		cub->step.y = -1;
		cub->sideDist.y = (cub->pos.y - cub->w_map.y) * cub->deltaDist.y;
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
		if (cub->map[cub->w_map.y][cub->w_map.x] == '1')
			cub->hit = 1;
	}
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

static void		ft_draw_pixel(t_cub *cub, t_color color, int x, int y)
{
	cub->scr.data[4 * x + 4 * cub->reso.x * y + 0] = color.red;
	cub->scr.data[4 * x + 4 * cub->reso.x * y + 1] = color.green;
	cub->scr.data[4 * x + 4 * cub->reso.x * y + 2] = color.blue;
	
}

static t_color	ft_tex_color(t_cub *cub)
{
	double wallX;

	wallX = (cub->side) ? cub->pos.x + cub->perpWallDist * cub->rayDir.x :
		cub->pos.y + cub->perpWallDist * cub->rayDir.y;
	wallX -= floor((wallX));
}

static void		ft_draw_columns(t_cub *cub, int x, int t)
{
	int i;
	t_color c;

	c.red = 255;
	c.green = 255;
	c.blue = 255;
	i = -1;
	(void)t;
	while (++i < cub->drawStart)
		ft_draw_pixel(cub, cub->ceiling, x, i);
	cub->drawStart--;
	while (++cub->drawStart < cub->drawEnd)
		ft_draw_pixel(cub, ft_tex_color(NULL), x, cub->drawStart);
	while (++cub->drawStart < cub->reso.y)
		ft_draw_pixel(cub, cub->floor, x, cub->drawStart);
}

static int		ft_guess_orientation(t_cub *cub)
{
	if (!cub->side)
		return ((cub->rayDir.x >= 0) ? 3 : 2);
	else
		return ((cub->rayDir.y >= 0) ? 0 : 1);
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
		ft_draw_columns(cub, x, ft_guess_orientation(cub));
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->scr.img_ptr, 0, 0);
}
