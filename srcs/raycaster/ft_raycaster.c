/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raytracer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 20:03:36 by grezette          #+#    #+#             */
/*   Updated: 2020/09/11 15:57:46 by grezette         ###   ########.fr       */
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
	step = 1.0 * cub->txtr[t].h / cub->lineheight;
	texpos = (cub->drawstart - cub->reso.y / 2 + cub->lineheight / 2) * step;
	while (cub->drawstart++ < cub->drawend)
	{
		texy = (int)texpos & (cub->txtr[t].h - 1);
		texpos += step;
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 0] =
			cub->txtr[t].data[texy * cub->txtr[t].h * 4 + texx * 4];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 1] =
			cub->txtr[t].data[texy * cub->txtr[t].h * 4 + texx * 4 + 1];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 2] =
			cub->txtr[t].data[texy * cub->txtr[t].h * 4 + texx * 4 + 2];
		cub->scr.data[4 * x + 4 * cub->reso.x * cub->drawstart + 3] =
			cub->txtr[t].data[texy * cub->txtr[t].h * 4 + texx * 4 + 3];
	}
}

static void	ft_draw_columns(t_cub *cub, int x, int t)
{
	int		i;

	i = -1;
	while (++i < cub->drawstart)
		ft_draw_pixel(cub, cub->ceiling, x, i);
	cub->drawstart -= 2;
	while (++cub->drawstart < cub->drawend)
		ft_tex_color(cub, t, x);
	cub->drawstart -= 2;
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
		cub->z_buffer[x] = cub->perpwalldist;
	}
	ft_sprite_casting(cub);
}

int			loop_hook(void *param)
{
	t_cub	*cub;
	double	tmp_dirx;
	double	tmp_planex;

	cub = (t_cub *)param;
	ft_raycaster(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->scr.img_ptr, 0, 0);
	tmp_dirx = cub->dir.x;
	tmp_planex = cub->plane.x;
	ft_move_left_right(cub);
	ft_move_forback(cub);
	ft_cam_hook(cub, tmp_dirx, tmp_planex);
	ft_swap(&cub->scr, &cub->scr_two);
	if (cub->key[4])
		ft_exit_error("No just kidding\n", NULL, cub, 0);
	return (0);
}
