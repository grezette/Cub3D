/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:20:17 by grezette          #+#    #+#             */
/*   Updated: 2020/01/26 21:19:46 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <mlx.h>
#include <math.h>
#include "../../Libft/libft.h"
#include <stdio.h>

# define X11_KEY_PRESS          2
# define X11_KEY_PRESS_M        1
# define X11_KEY_RELEASE        3
# define X11_KEY_RELEASE_M      2

typedef struct	s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		x;
	int		y;
	char	key[5];
}				t_cub;

int		hook(void *param)
{
	(void)param;
	return (0);
}

int		draw_window(t_cub *var, int color)
{
	int	tmpx;
	int tmpy;

	tmpx = var->x;
	tmpy = var->y;
	while (++var->y < tmpy + 125)
	{
		var->x = tmpx;
		while (var->x < tmpx + 125)
			mlx_pixel_put(var->mlx_ptr, var->win_ptr, var->x++, var->y, color);
	}
	var->x = tmpx;
	var->y = tmpy;
	return (0);
}

int		loop_hook(void *param)
{
	t_cub *var;

	var = (t_cub *)param;
	if (var->key[0])
	{
		draw_window(var, 0);
		if (var->x > 0)
			var->x -= 5;
		draw_window(var, 200);
	}
	if (var->key[1])
	{	
		draw_window(var, 0);
		if (var->x < 500)
			var->x += 5;
		draw_window(var, 200);
	}
	if (var->key[2])
	{
		draw_window(var, 0);
		if (var->y < 500)
			var->y += 5;
		draw_window(var, 200);
	}
	if (var->key[3])
	{
		draw_window(var, 0);
		if (var->y > 0)
			var->y -= 5;
		draw_window(var, 200);
	}
	if (var->key[4])
		exit(0);
	return (0);
}

int		key_hook_release(int keycode, void *param)
{
	t_cub *var;

	var = (t_cub *)param;
	if (keycode == 123)
		var->key[0] = 0 ;
	else if (keycode == 124)
		var->key[1] = 0;
	else if (keycode == 125)
		var->key[2] = 0;
	else if (keycode == 126)
		var->key[3] = 0;
	else if (keycode == 53)
		var->key[4] = 0;
	return (0);
}
int		key_hook_press(int keycode, void *param)
{
	t_cub *var;

	printf("%d\n", keycode);
	var = (t_cub *)param;
	if (keycode == 123)
		var->key[0] = 1;
	else if (keycode == 124)
		var->key[1] = 1;
	else if (keycode == 125)
		var->key[2] = 1;
	else if (keycode == 126)
		var->key[3] = 1;
	else if (keycode == 53)
		var->key[4] = 1;
	return (0);
}

int		main(void)
{
	t_cub var;

	var.x = 125;
	var.y = 125;
	var.key[0] = 0;
	var.key[1] = 0;
	var.key[2] = 0;
	var.key[3] = 0;
	var.key[4] = 0;
	var.mlx_ptr = mlx_init();
	var.win_ptr = mlx_new_window(var.mlx_ptr, 500, 500, "mlx_ptr");
	draw_window(&var, 200);
	mlx_loop_hook(var.mlx_ptr, &hook, &var);
	mlx_hook(var.win_ptr, X11_KEY_PRESS, X11_KEY_PRESS_M, &key_hook_press, &var);
	mlx_hook(var.win_ptr, X11_KEY_RELEASE, X11_KEY_RELEASE_M, &key_hook_release, &var);
	mlx_loop(var.mlx_ptr);
	return (0);
}
