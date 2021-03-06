/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 17:29:07 by grezette          #+#    #+#             */
/*   Updated: 2020/09/11 15:57:12 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void
	ft_cam_hook(t_cub *cub, double tmp_dirx, double tmp_planex)
{
	if (cub->key[5])
	{
		cub->dir.x = cub->dir.x * cos(-cub->rotspeed) -
			cub->dir.y * sin(-cub->rotspeed);
		cub->dir.y = tmp_dirx * sin(-cub->rotspeed) +
			cub->dir.y * cos(-cub->rotspeed);
		cub->plane.x = cub->plane.x * cos(-cub->rotspeed) -
			cub->plane.y * sin(-cub->rotspeed);
		cub->plane.y = tmp_planex * sin(-cub->rotspeed) +
			cub->plane.y * cos(-cub->rotspeed);
	}
	else if (cub->key[6])
	{
		cub->dir.x = cub->dir.x * cos(cub->rotspeed) -
			cub->dir.y * sin(cub->rotspeed);
		cub->dir.y = tmp_dirx * sin(cub->rotspeed) +
			cub->dir.y * cos(cub->rotspeed);
		cub->plane.x = cub->plane.x * cos(cub->rotspeed) -
			cub->plane.y * sin(cub->rotspeed);
		cub->plane.y = tmp_planex * sin(cub->rotspeed) +
			cub->plane.y * cos(cub->rotspeed);
	}
}

void
	ft_move_forback(t_cub *cub)
{
	if (cub->key[0])
	{
		if (cub->map[(int)cub->pos.y][(int)(cub->pos.x + cub->dir.x *
					cub->movespeed)] != '1')
			cub->pos.x = cub->pos.x + cub->dir.x * cub->movespeed;
		if (cub->map[(int)(cub->pos.y + cub->dir.y *
					cub->movespeed)][(int)cub->pos.x] != '1')
			cub->pos.y = cub->pos.y + cub->dir.y * cub->movespeed;
	}
	if (cub->key[1])
	{
		if (cub->map[(int)cub->pos.y][(int)(cub->pos.x + cub->dir.y *
					cub->movespeed / 2)] != '1')
			cub->pos.x = cub->pos.x + cub->dir.y * cub->movespeed / 2;
		if (cub->map[(int)(cub->pos.y - cub->dir.x *
					cub->movespeed / 2)][(int)cub->pos.x] != '1')
			cub->pos.y = cub->pos.y - cub->dir.x * cub->movespeed / 2;
	}
}

void
	ft_move_left_right(t_cub *cub)
{
	if (cub->key[2])
	{
		if (cub->map[(int)cub->pos.y][(int)(cub->pos.x - cub->dir.x *
					cub->movespeed)] != '1')
			cub->pos.x = cub->pos.x - cub->dir.x * cub->movespeed;
		if (cub->map[(int)(cub->pos.y - cub->dir.y *
					cub->movespeed)][(int)cub->pos.x] != '1')
			cub->pos.y = cub->pos.y - cub->dir.y * cub->movespeed;
	}
	if (cub->key[3])
	{
		if (cub->map[(int)cub->pos.y][(int)(cub->pos.x - cub->dir.y *
					cub->movespeed / 2)] != '1')
			cub->pos.x = cub->pos.x - cub->dir.y * cub->movespeed / 2;
		if (cub->map[(int)(cub->pos.y + cub->dir.x *
					cub->movespeed / 2)][(int)cub->pos.x] != '1')
			cub->pos.y = cub->pos.y + cub->dir.x * cub->movespeed / 2;
	}
}

int
	key_hook_release(int keycode, void *param)
{
	t_cub *var;

	var = (t_cub *)param;
	if (keycode == 119)
		var->key[0] = 0;
	else if (keycode == 97)
		var->key[1] = 0;
	else if (keycode == 115)
		var->key[2] = 0;
	else if (keycode == 100)
		var->key[3] = 0;
	else if (keycode == 65307)
		var->key[4] = 0;
	else if (keycode == 65361)
		var->key[5] = 0;
	else if (keycode == 65363)
		var->key[6] = 0;
	return (0);
}

int
	key_hook_press(int keycode, void *param)
{
	t_cub *var;

	var = (t_cub *)param;
	if (keycode == 119)
		var->key[0] = 1;
	else if (keycode == 97)
		var->key[1] = 1;
	else if (keycode == 115)
		var->key[2] = 1;
	else if (keycode == 100)
		var->key[3] = 1;
	else if (keycode == 65307)
		var->key[4] = 1;
	else if (keycode == 65361)
		var->key[5] = 1;
	else if (keycode == 65363)
		var->key[6] = 1;
	else if (keycode == 46 && var->key[7] == 0)
		var->key[7] = 1;
	else if (keycode == 46 && var->key[7] == 1)
		var->key[7] = 0;
	return (0);
}
