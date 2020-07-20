/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 20:03:36 by grezette          #+#    #+#             */
/*   Updated: 2020/07/20 17:58:24 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_draw_pixel(t_cub *cub, t_color color, int x, int y)
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
	texx = (int)((wallx - floor(wallx)) * (double)cub->txtr[t].width);
	texx = (t == 3 || t == 1) ? cub->txtr[t].width - texx - 1 : texx;
	step = 1.0 * cub->txtr[t].height / cub->lineheight;
	texpos = (cub->drawstart - cub->reso.y / 2 + cub->lineheight / 2) * step;
	while (++cub->drawstart < cub->drawend)
	{
		texy = (int)texpos & (cub->txtr[t].height - 1);
		texpos += step;
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 0] =
			cub->txtr[t].data[texy * cub->txtr[t].height * 4 + texx * 4];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 1] =
			cub->txtr[t].data[texy * cub->txtr[t].height * 4 + texx * 4 + 1];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 2] =
			cub->txtr[t].data[texy * cub->txtr[t].height * 4 + texx * 4 + 2];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 3] =
			cub->txtr[t].data[texy * cub->txtr[t].height * 4 + texx * 4 + 3];
	}
}

static void	ft_draw_columns(t_cub *cub, int x, int t)
{
	int		i;
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

void		ft_raycaster(t_cub *cub)
{
	int	x;

	x = -1;
	while (++x < cub->reso.x)
	{
		cub->camerax = 2 * x / (double)cub->reso.x - 1;
		cub->raydir.x = cub->dir.x + cub->plane.x * cub->camerax;
		cub->raydir.y = cub->dir.y + cub->plane.y * cub->camerax;
		cub->w_map.x = (int)cub->pos.x;
		cub->w_map.y = (int)cub->pos.y;
		cub->deltadist.x = (cub->raydir.x < 0) ? 1 / cub->raydir.x * -1 :
			1 / cub->raydir.x;
		cub->deltadist.y = (cub->raydir.y < 0) ? 1 / cub->raydir.y * -1 :
			1 / cub->raydir.y;
		cub->hit = 0;
		ft_if_raydir(cub);
		ft_rayt_dda(cub);
		ft_rayt_height(cub);
		ft_draw_columns(cub, x, ft_guess_orientation(cub));
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->scr.img_ptr, 0, 0);
}
