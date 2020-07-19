/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 20:03:36 by grezette          #+#    #+#             */
/*   Updated: 2020/07/19 18:26:11 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static	void	ft_init_raytracer(t_cub *cub, int x)
{
	cub->camerax = 2 * x / (double)cub->reso.x - 1;
	cub->raydir.x = cub->dir.x + cub->plane.x * cub->camerax;
	cub->raydir.y = cub->dir.y + cub->plane.y * cub->camerax;
	cub->w_map.x = (int)cub->pos.x;
	cub->w_map.y = (int)cub->pos.y;
	cub->deltadist.x = (cub->raydir.x < 0) ? 1 / cub->raydir.x * -1 : \
					1 / cub->raydir.x;
	cub->deltadist.y = (cub->raydir.y < 0) ? 1 / cub->raydir.y * -1 : \
					1 / cub->raydir.y;
	cub->hit = 0;
}

static	void	ft_if_raydir(t_cub *cub)
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

static	void	ft_rayt_dda(t_cub *cub)
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
	cub->perpwalldist = (cub->side == 0) ? (cub->w_map.x - cub->pos.x + \
			(1 - cub->step.x) / 2) / cub->raydir.x : (cub->w_map.y - \
				cub->pos.y + (1 - cub->step.y) / 2) / cub->raydir.y;
}

static	void	ft_rayt_height(t_cub *cub)
{
	cub->lineheight = (int)(cub->reso.y / cub->perpwalldist);
	cub->drawstart = -cub->lineheight / 2 + cub->reso.y / 2;
	cub->drawstart = (cub->drawstart < 0) ? 0 : cub->drawstart;
	cub->drawend = cub->lineheight / 2 + cub->reso.y / 2;
	if (cub->drawend >= cub->reso.y)
		cub->drawend = cub->reso.y - 1;
}

static void		ft_draw_pixel(t_cub *cub, t_color color, int x, int y)
{
	cub->scr.data[4 * x + 4 * cub->reso.x * y + 0] = color.red;
	cub->scr.data[4 * x + 4 * cub->reso.x * y + 1] = color.green;
	cub->scr.data[4 * x + 4 * cub->reso.x * y + 2] = color.blue;
}

static void	ft_tex_color(t_cub *cub, int t, int x)
{
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;

	wallx = (cub->side) ? cub->pos.x + cub->perpwalldist * cub->raydir.x :
		cub->pos.y + cub->perpwalldist * cub->raydir.y;
	wallx -= floor((wallx));
	texx = (int)(wallx * (double)cub->txtr[t].width);
	texx = (t == 3 || t == 1) ? cub->txtr[t].width - texx - 1 : texx;
	step = 1.0 * cub->txtr[t].height / cub->lineheight;
	texpos = (cub->drawstart - cub->reso.y / 2 + cub->lineheight / 2) * step;
	while (++cub->drawstart < cub->drawend)
	{
		texy = (int)texpos & (cub->txtr[t].height - 1);
		texpos += step;
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 0] = \
			cub->txtr[t].data[texy * cub->txtr[t].height + texx];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 1] = \
			cub->txtr[t].data[texy * cub->txtr[t].height + texx + 1];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 2] = \
			cub->txtr[t].data[texy * cub->txtr[t].height + texx + 2];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 3] = \
			cub->txtr[t].data[texy * cub->txtr[t].height + texx + 3];
	}
}

static void		ft_draw_columns(t_cub *cub, int x, int t)
{
	int i;
	t_color c;

	c.red = 255;
	c.green = 255;
	c.blue = 255;
	i = -1;
	while (++i < cub->drawstart)
		ft_draw_pixel(cub, cub->ceiling, x, i);
	cub->drawstart--;
	while (++cub->drawstart < cub->drawend)
		ft_tex_color(cub, t, x);
	while (++cub->drawstart < cub->reso.y)
		ft_draw_pixel(cub, cub->floor, x, cub->drawstart);
}

static int		ft_guess_orientation(t_cub *cub)
{
	if (!cub->side)
		return ((cub->raydir.x >= 0) ? 3 : 2);
	else
		return ((cub->raydir.y >= 0) ? 0 : 1);
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
