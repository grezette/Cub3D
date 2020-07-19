#include "../../include/cub3d.h"

static void	cam_hook(t_cub *cub)
{
	double	tmp_dirx;
	double	tmp_planex;

	tmp_dirx = cub->dir.x;
	tmp_planex = cub->plane.x;
	if (cub->key[5])
	{
		cub->dir.x = cub->dir.x * cos(-cub->rotspeed) - \
					 cub->dir.y * sin(-cub->rotspeed);
		cub->dir.y = tmp_dirx * sin(-cub->rotspeed) + \
					 cub->dir.y * cos(-cub->rotspeed);
		cub->plane.x = cub->plane.x * cos(-cub->rotspeed) - \
					   cub->plane.y * sin(-cub->rotspeed);
		cub->plane.y = tmp_planex * sin(-cub->rotspeed) + \
					   cub->plane.y * cos(-cub->rotspeed);
	}
	else if (cub->key[6])
	{
		cub->dir.x = cub->dir.x * cos(cub->rotspeed) - \
					 cub->dir.y * sin(cub->rotspeed);
		cub->dir.y = tmp_dirx * sin(cub->rotspeed) + \
					 cub->dir.y * cos(cub->rotspeed);
		cub->plane.x = cub->plane.x * cos(cub->rotspeed) - \
					   cub->plane.y * sin(cub->rotspeed);
		cub->plane.y = tmp_planex * sin(cub->rotspeed) + \
					   cub->plane.y * cos(cub->rotspeed);
	}
}

int		loop_hook(void *param)
{
	t_cub *cub;

	cub = (t_cub *)param;
	ft_raytracer(cub);
	if (cub->key[0])
	{
		if (cub->map[(int)cub->pos.y][(int)(cub->pos.x + cub->dir.x * cub->movespeed)] != '1')
			cub->pos.x = cub->pos.x + cub->dir.x * cub->movespeed;
		if (cub->map[(int)(cub->pos.y + cub->dir.y * cub->movespeed)][(int)cub->pos.x] != '1')
			cub->pos.y = cub->pos.y + cub->dir.y * cub->movespeed;
	}
	if (cub->key[1])
	{
		if (cub->map[(int)cub->pos.y][(int)(cub->pos.x + cub->dir.y * cub->movespeed / 2)] != '1')
			cub->pos.x = cub->pos.x + cub->dir.y * cub->movespeed / 2;
		if (cub->map[(int)(cub->pos.y - cub->dir.x * cub->movespeed / 2)][(int)cub->pos.x] != '1')
			cub->pos.y = cub->pos.y - cub->dir.x * cub->movespeed / 2;
	}
	if (cub->key[2])
	{
		if (cub->map[(int)cub->pos.y][(int)(cub->pos.x - cub->dir.x * cub->movespeed)] != '1')
			cub->pos.x = cub->pos.x - cub->dir.x * cub->movespeed;
		if (cub->map[(int)(cub->pos.y - cub->dir.y * cub->movespeed)][(int)cub->pos.x] != '1')
			cub->pos.y = cub->pos.y - cub->dir.y * cub->movespeed;
	}
	if (cub->key[3])
	{
		if (cub->map[(int)cub->pos.y][(int)(cub->pos.x - cub->dir.y * cub->movespeed / 2)] != '1')
			cub->pos.x = cub->pos.x - cub->dir.y * cub->movespeed / 2;
		if (cub->map[(int)(cub->pos.y + cub->dir.x * cub->movespeed / 2)][(int)cub->pos.x] != '1')
			cub->pos.y = cub->pos.y + cub->dir.x * cub->movespeed / 2;
	}
	if (cub->key[4])
		ft_exit_error("No just kidding\n", NULL, cub, 0);
	cam_hook(cub);
	return (0);
}

int		key_hook_release(int keycode, void *param)
{
	t_cub *var;

	var = (t_cub *)param;
	if (keycode == 13)
		var->key[0] = 0;
	else if (keycode == 0)
		var->key[1] = 0;
	else if (keycode == 1)
		var->key[2] = 0;
	else if (keycode == 2)
		var->key[3] = 0;
	else if (keycode == 53)
		var->key[4] = 0;
	else if (keycode == 123)
		var->key[5] = 0;
	else if (keycode == 124)
		var->key[6] = 0;
	return (0);
}

int		key_hook_press(int keycode, void *param)
{
	t_cub *var;

	var = (t_cub *)param;
	if (keycode == 13) //devant
		var->key[0] = 1 ;
	else if (keycode == 0) //gauche
		var->key[1] = 1;
	else if (keycode == 1) //derriere
		var->key[2] = 1;
	else if (keycode == 2) //droite
		var->key[3] = 1;
	else if (keycode == 53) //echap
		var->key[4] = 1;
	else if (keycode == 123) //camera gauche
		var->key[5] = 1;
	else if (keycode == 124) // camera droite
		var->key[6] = 1;
	else if (keycode == 46 && var->key[7] == 0)
		var->key[7] = 1;
	else if (keycode == 46 && var->key[7] == 1)
		var->key[7] = 0;
	return (0);
}
