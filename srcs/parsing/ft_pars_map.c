/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 17:17:21 by grezette          #+#    #+#             */
/*   Updated: 2020/08/10 16:48:38 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	ft_check_char_map(char **map)
{
	int i;
	int j;
	int bol;

	i = -1;
	bol = 0;
	while (map[++i] && (j = -1))
		while (map[i][++j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' ||
						map[i][j] == 'W') && bol)
				return (-1);
			else if ((map[i][j] == 'N' || map[i][j] == 'S' ||
						map[i][j] == 'E' || map[i][j] == 'W') && !bol)
				bol = 1;
			else if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' &&
					map[i][j] != 'W' && map[i][j] != ' ' && map[i][j] != '0' &&
					map[i][j] != '1' && map[i][j] != '2' && map[i][j] != '\f' &&
					map[i][j] != '\t' && map[i][j] != '\r' && map[i][j] != '\v')
				return (-1);
		}
	if (bol == 0)
		return (-1);
	return (0);
}

static void	flood_fill(char **map, int x, int y, t_cub *cub)
{
	map[y][x] = '1';
	if (!map[y][x + 1] || !map[y + 1] || x - 1 < 0 || y - 1 < 0 ||
			(int)ft_strlen(map[y + 1]) < x || (int)ft_strlen(map[y - 1]) < x ||
			ft_isspace(map[y][x + 1]) || ft_isspace(map[y][x - 1]) ||
			ft_isspace(map[y + 1][x]) || ft_isspace(map[y + 1][x]))
	{
		map = ft_square_free(map);
		ft_exit_error("Map not closed\n", NULL, cub, 0);
	}
	if (map[y][x + 1] != '1')
		flood_fill(map, x + 1, y, cub);
	if (map[y][x - 1] != '1')
		flood_fill(map, x - 1, y, cub);
	if (map[y + 1][x] != '1')
		flood_fill(map, x, y + 1, cub);
	if (map[y - 1][x] != '1')
		flood_fill(map, x, y - 1, cub);
}

static void	ft_pars_map2(t_cub *cub)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	x = 0;
	map = NULL;
	if (!(map = ft_square_strjoin(cub->map, NULL)))
		ft_exit_error("Square_strjoin failed", NULL, cub, 0);
	while (map[y] && map[y][x] != 'N' && map[y][x] != 'W' && map[y][x] != 'E' &&
			map[y][x] != 'S')
	{
		x = 0;
		while (map[y][x] && map[y][x] != 'N' && map[y][x] != 'W' &&
				map[y][x] != 'E' && map[y][x] != 'S')
			x++;
		if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E' ||
				map[y][x] == 'S')
			break ;
		y++;
	}
	flood_fill(map, x, y, cub);
	map = ft_square_free(map);
}

char		**ft_adjust_map(char **map)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!(str = (char **)malloc(sizeof(char *) *
					(ft_minimap_good_size(map) + 2))))
		return (NULL);
	while (map[i])
	{
		j = 0;
		while (map[i][j] && ft_isspace(map[i][j]))
			j++;
		if (map[i][j])
			break ;
		i++;
	}
	while (k <= ft_minimap_good_size(map))
		if (!(str[k++] = ft_strdup(map[i++])))
			return (ft_square_free(str));
	str[k] = NULL;
	ft_square_free(map);
	return (str);
}

void		ft_pars_map(t_cub *cub, int fd)
{
	char	**tmp;
	char	*line;
	int		ret;

	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			ft_exit_error("Parsing: 'Get_Next_Line' failed\n", NULL, cub, fd);
		if (!(tmp = ft_square_strjoin(cub->map, line)))
			ft_exit_error("Parsing: 'square_strjoin' failed\n", line, cub, fd);
		ft_square_free(cub->map);
		cub->map = tmp;
		free(line);
		line = NULL;
	}
	free(line);
	if (close(fd) == -1)
		ft_exit_error("'Close' failed", NULL, cub, 0);
	if (ft_check_char_map(cub->map))
		ft_exit_error("Parsing: Wrong char in map\n", NULL, cub, 0);
	if (!(cub->map = ft_adjust_map(cub->map)))
		ft_exit_error("Parsing: adjust_map failed\n", NULL, cub, 0);
	ft_pars_map2(cub);
}
