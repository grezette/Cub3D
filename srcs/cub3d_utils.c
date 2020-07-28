/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:01:14 by grezette          #+#    #+#             */
/*   Updated: 2020/07/27 17:33:24 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void			ft_exit_error(char *msg, void *elem, t_cub *cub, int fd)
{
	int i;

	i = -1;
	write(1, "error\n", 6);
	write(1, msg, ft_strlen(msg));
	free(elem);
	if (cub)
	{
		free(cub->n_txtr);
		free(cub->s_txtr);
		free(cub->w_txtr);
		free(cub->e_txtr);
		free(cub->spt_txtr);
		if (cub->map)
			while (cub->map[++i])
				free(cub->map[i]);
		free(cub->map);
	}
	if (fd)
		if (close(fd) == -1)
			write(1, "'close' failed as well\n", 22);
	exit(0);
}

static t_coord	ft_guess_start_position(char **map)
{
	t_coord	pos;
	int		i;
	int		j;

	i = 0;
	while (map[++i])
	{
		j = 0;
		pos.y = (double)i;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
					map[i][j] == 'W' || map[i][j] == 'E')
			{
				pos.x = (double)j;
				return (pos);
			}
		}
	}
	return (pos);
}

static t_coord	ft_guess_start_direction(char **map, int x, int y)
{
	t_coord dir;

	if (map[y][x] == 'N')
	{
		dir.x = 0;
		dir.y = -1;
	}
	if (map[y][x] == 'S')
	{
		dir.x = 0;
		dir.y = 1;
	}
	if (map[y][x] == 'E')
	{
		dir.x = 1;
		dir.y = 0;
	}
	if (map[y][x] == '0')
	{
		dir.x = -1;
		dir.y = 0;
	}
	map[y][x] = '0';
	return (dir);
}

static void		ft_get_textures(t_cub *cub)
{
	if (!(cub->txtr[0].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->n_txtr, &((cub->txtr[0]).width),
					&(cub->txtr[0].height))))
		ft_exit_error("North path not valid", NULL, cub, 0);
	cub->txtr[0].data = mlx_get_data_addr(cub->txtr[0].img_ptr,
			&cub->txtr[0].bpp, &cub->txtr[0].size_l, &cub->txtr[0].endian);
	if (!(cub->txtr[1].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->s_txtr, &((cub->txtr[1]).width),
					&(cub->txtr[1].height))))
		ft_exit_error("South path not valid", NULL, cub, 0);
	cub->txtr[1].data = mlx_get_data_addr(cub->txtr[1].img_ptr,
			&cub->txtr[1].bpp, &cub->txtr[1].size_l, &cub->txtr[1].endian);
	if (!(cub->txtr[2].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->e_txtr, &((cub->txtr[2]).width),
					&(cub->txtr[2].height))))
		ft_exit_error("East path not valid", NULL, cub, 0);
	cub->txtr[2].data = mlx_get_data_addr(cub->txtr[2].img_ptr,
			&cub->txtr[2].bpp, &cub->txtr[2].size_l, &cub->txtr[2].endian);
	if (!(cub->txtr[3].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->w_txtr, &((cub->txtr[3]).width),
					&(cub->txtr[3].height))))
		ft_exit_error("West path not valid", NULL, cub, 0);
	cub->txtr[3].data = mlx_get_data_addr(cub->txtr[3].img_ptr,
			&cub->txtr[3].bpp, &cub->txtr[3].size_l, &cub->txtr[3].endian);
}

void			ft_minilibx_init(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->reso.x, \
			cub->reso.y, "Cub3D");
	cub->scr.img_ptr = mlx_new_image(cub->mlx_ptr, cub->reso.x, \
			cub->reso.y);
	cub->scr.data = mlx_get_data_addr(cub->scr.img_ptr, &(cub->scr.bpp), \
			&(cub->scr.size_l), &(cub->scr.endian));
	cub->pos = ft_guess_start_position(cub->map);
	cub->dir = ft_guess_start_direction(cub->map, cub->pos.x, cub->pos.y);
	cub->plane.x = 0.85;
	cub->plane.y = 0.0;
	cub->movespeed = 0.033 * 5.0;
	cub->rotspeed = 0.033 * 3.0;
	ft_bzero(cub->key, sizeof(int) * 6);
	if (!(cub->z_buffer = (double *)malloc(sizeof(double) * cub->reso.x)))
		ft_exit_error("minilibx_init failed", NULL, cub, 0);
	ft_get_textures(cub);
}
