/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:01:14 by grezette          #+#    #+#             */
/*   Updated: 2020/08/01 16:26:02 by grezette         ###   ########.fr       */
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

static void		ft_get_sprt_info(t_cub *cub)
{
	int i;
	int j;
	int k;

	i = -1;
	k = -1;
	cub->nb_sprt = 0;
	while (!(j = -1) || cub->map[++i])
		while (cub->map[i][++j])
			if (cub->map[i][j] == '2')
				cub->nb_sprt++;
	if (!(cub->sprt = (t_coord *)malloc(sizeof(t_coord) * cub->nb_sprt)) ||
			!(cub->sprt_order = (int *)malloc(sizeof(int) * cub->nb_sprt)) ||
			!(cub->sprt_dist = (double *)malloc(sizeof(double) * cub->nb_sprt)))
		ft_exit_error("get_sprt_info failed", NULL, cub, 0);
	i = -1;
	while (!(j = -1) || cub->map[++i])
		while (cub->map[i][++j])
			if (cub->map[i][j] == '2')
			{
				cub->sprt[++k].x = (double)j + 0.5;
				cub->sprt[k].y = (double)i + 0.5;
			}
}

static t_coord	ft_guess_start_position(char **map)
{
	t_coord	pos;
	int		i;
	int		j;

	i = -1;
	while (++i <= (int)ft_square_strlen(map))
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

static void	ft_set_orientation(t_cub *cub, double diry, double plx, double ply)
{
	cub->dir.y = diry;
	cub->plane.x = plx;
	cub->plane.y = ply;
}

static void	ft_guess_start_direction(t_cub *cub, int x, int y)
{
	if (cub->map[y][x] == 'N')
	{
		cub->dir.x = 0;
		ft_set_orientation(cub, -1, 0.85, 0.0);
	}
	else if (cub->map[y][x] == 'S')
	{
		cub->dir.x = 0;
		ft_set_orientation(cub, 1, -0.85, 0.0);
	}
	else if (cub->map[y][x] == 'E')
	{
		cub->dir.x = 1;
		ft_set_orientation(cub, 0, 0.0, 0.85);
	}
	else
	{
		cub->dir.x = -1;
		ft_set_orientation(cub, 0, 0.0, -0.85);
	}
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
	ft_guess_start_direction(cub, cub->pos.x, cub->pos.y);
	cub->movespeed = 0.033 * 3.0;
	cub->rotspeed = 0.033 * 1.8;
	ft_bzero(cub->key, sizeof(int) * 8);
	if (!(cub->z_buffer = (double *)malloc(sizeof(double) * cub->reso.x)))
		ft_exit_error("minilibx_init failed", NULL, cub, 0);
	ft_get_textures(cub);
	ft_get_sprt_info(cub);
	if (!(cub->spt_img.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->spt_txtr, &(cub->spt_img.width),
					&(cub->spt_img.height))))
		ft_exit_error("Sprite path not valid", NULL, cub, 0);
	cub->spt_img.data = mlx_get_data_addr(cub->spt_img.img_ptr,
			&cub->spt_img.bpp, &cub->spt_img.size_l, &cub->spt_img.endian);
}
