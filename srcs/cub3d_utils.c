/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:01:14 by grezette          #+#    #+#             */
/*   Updated: 2020/09/11 16:12:50 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int				ft_width_map(char **map)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (map[++i])
		len = (len >= (int)ft_strlen(map[i]) ? len : (int)ft_strlen(map[i]));
	return (len);
}

int				ft_minimap_good_size(char **map)
{
	int i;
	int j;
	int height;

	i = -1;
	height = (int)ft_square_strlen(map);
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && ft_isspace(map[i][j]))
			j++;
		if (map[i][j])
			break ;
	}
	height -= i;
	i = (int)ft_square_strlen(map);
	while (--i)
	{
		j = 0;
		while (map[i][j] && ft_isspace(map[i][j]))
			j++;
		if (map[i][j])
			break ;
	}
	return (height + i - ft_square_strlen(map));
}

void			ft_draw_header(t_cub *cub, int fd)
{
	int tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * cub->reso.x * cub->reso.y;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &cub->reso.x, 4);
	write(fd, &cub->reso.y, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &cub->scr.bpp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

static void		ft_get_textures(t_cub *cub)
{
	if (!(cub->txtr[0].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->n_txtr, &((cub->txtr[0]).width),
					&(cub->txtr[0].h))))
		ft_exit_error("North path not valid", NULL, cub, 0);
	if (!(cub->txtr[0].data = mlx_get_data_addr(cub->txtr[0].img_ptr,
					&cub->txtr[0].bpp, &cub->txtr[0].size_l,
					&cub->txtr[0].endian)))
		ft_exit_error("mlx_get_data_addr failed\n", NULL, cub, 0);
	if (!(cub->txtr[1].img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->s_txtr, &((cub->txtr[1]).width),
					&(cub->txtr[1].h))))
		ft_exit_error("South path not valid", NULL, cub, 0);
	if (!(cub->txtr[1].data = mlx_get_data_addr(cub->txtr[1].img_ptr,
					&cub->txtr[1].bpp, &cub->txtr[1].size_l,
					&cub->txtr[1].endian)))
		ft_exit_error("mlx_get_data_addr failed\n", NULL, cub, 0);
	if (!(cub->spt_img.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->spt_txtr, &(cub->spt_img.width),
					&(cub->spt_img.h))))
		ft_exit_error("Sprite path not valid", NULL, cub, 0);
	if (!(cub->spt_img.data = mlx_get_data_addr(cub->spt_img.img_ptr,
					&cub->spt_img.bpp, &cub->spt_img.size_l,
					&cub->spt_img.endian)))
		ft_exit_error("mlx_get_data_addr failed\n", NULL, cub, 0);
	ft_get_textures_2(cub);
}

void			ft_minilibx_init(t_cub *cub)
{
	t_reso	size;

	if (!(cub->mlx_ptr = mlx_init()))
		ft_exit_error("mlx_init failed\n", NULL, cub, 0);
	mlx_get_screen_size(cub->mlx_ptr, &size.x, &size.y);
	cub->reso.x = (cub->reso.x > size.x) ? size.x : cub->reso.x;
	cub->reso.y = (cub->reso.y > size.y) ? size.y : cub->reso.y;
	if (!(cub->scr.img_ptr = mlx_new_image(cub->mlx_ptr,
					cub->reso.x, cub->reso.y)))
		ft_exit_error("mlx_new_image failed\n", NULL, cub, 0);
	if (!(cub->scr.data = mlx_get_data_addr(cub->scr.img_ptr, &(cub->scr.bpp),
					&(cub->scr.size_l), &(cub->scr.endian))))
		ft_exit_error("mlx_get_data_addr failed\n", NULL, cub, 0);
	cub->pos = ft_guess_start_position(cub->map);
	ft_guess_start_direction(cub, cub->pos.x, cub->pos.y);
	cub->movespeed = 0.033 * 3.0;
	cub->rotspeed = 0.033 * 1.8;
	ft_bzero(cub->key, sizeof(int) * 8);
	ft_get_sprt_info(cub);
	if (!(cub->z_buffer = (double *)malloc(sizeof(double) * cub->reso.x)))
		ft_exit_error("minilibx_init failed", NULL, cub, 0);
	ft_get_textures(cub);
	if (!(cub->scr_two.data = mlx_get_data_addr(cub->scr_two.img_ptr,
	&(cub->scr_two.bpp), &(cub->scr_two.size_l), &(cub->scr_two.endian))))
		ft_exit_error("mlx_get_data_addr failed\n", NULL, cub, 0);
}
