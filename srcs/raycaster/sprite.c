/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 16:54:02 by grezette          #+#    #+#             */
/*   Updated: 2020/08/09 18:41:57 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_sort_sprite(t_cub *cub)
{
	int		i;
	int		j;
	double	tmp;

	i = -1;
	while (++i < cub->nb_sprt)
	{
		j = -1;
		while (++j < cub->nb_sprt - 1)
		{
			if (cub->sprt_dist[j] < cub->sprt_dist[j + 1])
			{
				tmp = cub->sprt_dist[j];
				cub->sprt_dist[j] = cub->sprt_dist[j + 1];
				cub->sprt_dist[j + 1] = tmp;
				tmp = cub->sprt_order[j];
				cub->sprt_order[j] = cub->sprt_order[j + 1];
				cub->sprt_order[j + 1] = (int)tmp;
			}
		}
	}
}

void	ft_sprite_sorting(t_cub *cub)
{
	int i;

	i = 0;
	while (++i < cub->nb_sprt)
	{
		cub->sprt_order[i] = i;
		cub->sprt_dist[i] = ((cub->pos.x - cub->sprt[i].x) *
				(cub->pos.x - cub->sprt[i].x) + (cub->pos.y -
					cub->sprt[i].y) * (cub->pos.y - cub->sprt[i].y));
	}
	ft_sort_sprite(cub);
}

void	ft_set_cal_sprite(t_cub *cub, int i)
{
	cub->spt_pos.x = cub->sprt[cub->sprt_order[i]].x - cub->pos.x;
	cub->spt_pos.y = cub->sprt[cub->sprt_order[i]].y - cub->pos.y;
	cub->invdet = 1.0 / (cub->plane.x * cub->dir.y - cub->dir.x * cub->plane.y);
	cub->transform.x = cub->invdet * (cub->dir.y * cub->spt_pos.x -
			cub->dir.x * cub->spt_pos.y);
	cub->transform.y = cub->invdet * (-cub->plane.y * cub->spt_pos.x +
			cub->plane.x * cub->spt_pos.y);
	cub->spritescreenx = (int)((cub->reso.x / 2) * (1 + cub->transform.x /
				cub->transform.y));
	cub->sprt_height = abs((int)(cub->reso.y / cub->transform.y));
	cub->spt_drawstart.y = -cub->sprt_height / 2 + cub->reso.y / 2;
	cub->spt_drawstart.y = (cub->spt_drawstart.y < 0) ? 0 :
		cub->spt_drawstart.y;
	cub->spt_drawend.y = cub->sprt_height / 2 + cub->reso.y / 2;
	cub->spt_drawend.y = (cub->spt_drawend.y >= cub->reso.y) ?
		cub->reso.y - 1 : cub->spt_drawend.y;
	cub->sprite_width = abs((int)(cub->reso.y / cub->transform.y));
	cub->spt_drawstart.x = -cub->sprite_width / 2 + cub->spritescreenx;
	cub->spt_drawstart.x = (cub->spt_drawstart.x < 0) ? 0 :
		cub->spt_drawstart.x;
	cub->spt_drawend.x = cub->sprite_width / 2 + cub->spritescreenx;
	cub->spt_drawend.x = (cub->spt_drawend.x >= cub->reso.x) ?
		cub->reso.x - 1 : cub->spt_drawend.x;
}

void	ft_draw_sprite(t_cub *cub, int stripe, int texx)
{
	int y;
	int d;
	int	texy;

	y = cub->spt_drawstart.y - 1;
	while (++y < cub->spt_drawend.y)
	{
		d = y * 256 - cub->reso.y * 128 + cub->sprt_height * 128;
		texy = ((d * cub->spt_img.h) / cub->sprt_height) / 256;
		if (cub->spt_img.data[4 * texy * cub->spt_img.h + 4 * texx] ||
				cub->spt_img.data[texy * cub->spt_img.h * 4 + texx * 4 + 1] ||
				cub->spt_img.data[texy * cub->spt_img.h * 4 + texx * 4 + 2] ||
				cub->spt_img.data[texy * cub->spt_img.h * 4 + texx * 4 + 3])
		{
			cub->scr.data[4 * stripe + 4 * cub->reso.x * y] =
				cub->spt_img.data[4 * texy * cub->spt_img.h + 4 * texx];
			cub->scr.data[4 * stripe + 4 * cub->reso.x * y + 1] =
				cub->spt_img.data[texy * cub->spt_img.h * 4 + texx * 4 + 1];
			cub->scr.data[4 * stripe + 4 * cub->reso.x * y + 2] =
				cub->spt_img.data[texy * cub->spt_img.h * 4 + texx * 4 + 2];
			cub->scr.data[4 * stripe + 4 * cub->reso.x * y + 3] =
				cub->spt_img.data[texy * cub->spt_img.h * 4 + texx * 4 + 3];
		}
	}
}

void	ft_sprite_casting(t_cub *cub)
{
	int	i;
	int	stripe;
	int	texx;

	i = -1;
	ft_sprite_sorting(cub);
	while (++i < cub->nb_sprt)
	{
		ft_set_cal_sprite(cub, i);
		stripe = cub->spt_drawstart.x - 1;
		while (++stripe < cub->spt_drawend.x)
		{
			texx = (int)(256 * (stripe - (-cub->sprite_width / 2 +
							cub->spritescreenx)) * cub->spt_img.width /
					cub->sprite_width) / 256;
			if (cub->transform.y > 0 && stripe > 0 && stripe < cub->reso.x &&
					cub->transform.y < cub->z_buffer[stripe])
				ft_draw_sprite(cub, stripe, texx);
		}
	}
}
