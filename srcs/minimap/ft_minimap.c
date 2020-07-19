/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:00:25 by grezette          #+#    #+#             */
/*   Updated: 2020/07/19 15:00:34 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_width_map(char **map)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (map[++i])
		len = (len >= (int)ft_strlen(map[i]) ? len : (int)ft_strlen(map[i]));
	return (len);
}

int		ft_minimap_good_size(char **map)
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

/*

   void	ft_wright_minimap(t_cub *cub, int x, int y, t_color col)
   {
   int max_x;
   int max_y;
   int tmp_x;

   max_x = (x + 1) * cub->reso.x / ft_width_map(cub->map) / 4;
   max_y = (y + 1) * cub->reso.y / ft_square_strlen(cub->map) / 4;
   x = x * cub->reso.x / ft_width_map(cub->map) / 4;
   y = y * cub->reso.y / ft_square_strlen(cub->map) / 4;
   tmp_x = x;
   while (++y < max_y)
   {
   x = tmp_x;
   while (x < max_x)
   {
   cub->data[4 * x + 4 * cub->reso.x * y] = (char)col.blue;
   cub->data[4 * x + 4 * cub->reso.x * y + 1] = (char)col.green;
   cub->data[4 * x + 4 * cub->reso.x * y + 2] = (char)col.red;
   x++;
   }
   }
   }
   */
/*penser à rajouter un bail qui déclare les couleur direct genre:*/
/*	'int wight; wight.red = 255, wight.green = 255, etc...*/

/*

   void	ft_minimap(t_cub *cub)
   {
   int x;
   int y;

   y = -1;
   while (cub->map[++y])
   {
   x = -1;
   while (cub->map[y][++x])
   {
   if (cub->map[y][x] == '1')
   ft_wright_minimap(cub, x, y, blue);
   if (cub->map[y][x] == '2')
   ft_wright_minimap(cub, x, y, green);
   if (cub->map[y][x] == '0')
   ft_wright_minimap(cub, x, y, wight);
   if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S' ||
   cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
   ft_wright_minimap(cub, x, y, red);
   }
   }
   mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img_ptr, 0, 0);
   }

*/
