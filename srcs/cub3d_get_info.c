/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_get_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:52:16 by grezette          #+#    #+#             */
/*   Updated: 2020/09/11 16:04:49 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_get_sprt_info(t_cub *cub)
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

t_coord		ft_guess_start_position(char **map)
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

void		ft_set_orientation(t_cub *cub, double diry, double plx, double ply)
{
	cub->dir.y = diry;
	cub->plane.x = plx;
	cub->plane.y = ply;
}

void		ft_guess_start_direction(t_cub *cub, int x, int y)
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

void		ft_get_textures_2(t_cub *cub)
{
	if (!(cub->scr_two.img_ptr = mlx_new_image(cub->mlx_ptr,
					cub->reso.x, cub->reso.y)))
		ft_exit_error("mlx_new_image failed\n", NULL, cub, 0);
	if (!(cub->scr_two.data = mlx_get_data_addr(cub->scr_two.img_ptr,
					&(cub->scr_two.bpp),
					&(cub->scr_two.size_l),
					&(cub->scr_two.endian))))
		ft_exit_error("mlx_get_data_addr failed\n", NULL, cub, 0);
	if (!(cub->txtr[2].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->e_txtr, &((cub->txtr[2]).width),
					&(cub->txtr[2].h))))
		ft_exit_error("East path not valid", NULL, cub, 0);
	if (!(cub->txtr[2].data = mlx_get_data_addr(cub->txtr[2].img_ptr,
					&cub->txtr[2].bpp, &cub->txtr[2].size_l,
					&cub->txtr[2].endian)))
		ft_exit_error("mlx_get_data_addr failed\n", NULL, cub, 0);
	if (!(cub->txtr[3].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->w_txtr, &((cub->txtr[3]).width),
					&(cub->txtr[3].h))))
		ft_exit_error("West path not valid", NULL, cub, 0);
	if (!(cub->txtr[3].data = mlx_get_data_addr(cub->txtr[3].img_ptr,
					&cub->txtr[3].bpp, &cub->txtr[3].size_l,
					&cub->txtr[3].endian)))
		ft_exit_error("mlx_get_data_addr failed\n", NULL, cub, 0);
}
