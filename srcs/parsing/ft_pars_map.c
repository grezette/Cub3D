#include "../../include/cub3d.h"
#include <stdio.h>

/*segfault si tab == NULL*/
/*faut supprimer ce commit pour la norm*/
static char	**ft_square_free(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

static char	**ft_square_strjoin(char **tab, char *str)
{
	char	**ret;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		if (!(ret[i] = ft_strdup(tab[i])))
			return (ft_square_free(ret));
	i = (i < 0) ? 0 : i;
	if (str)
		if (!(ret[i] = ft_strdup(str)))
			return (ft_square_free(ret));
	ret[i + 1] = NULL;
	return (ret);
}

static int	ft_check_char_map(char **map)
{
	int i;
	int j;
	int bol;

	i = -1;
	bol = 0;
	while (map[++i])
	{
		j = -1;
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
	}
	return (0);
}

/*voir pk ca segfault*/
void	flood_fill(char **map, int x, int y, t_cub *cub)
{
	map[y][x] = 1;
	write(1, "a", 1);
	if (!map[y][x + 1] || !map[y + 1] || x - 1 < 0 || y - 1 < 0)
	{
		ft_square_free(map);
		ft_exit_error("Map not closed", NULL, cub, 0);
	}
	else if (map[y][x + 1] != 1)
		flood_fill(map, y, x + 1, cub);
	else if (map[y][x - 1] != 1)
		flood_fill(map, y, x - 1, cub);
	else if (map[y + 1][x] != 1)
		flood_fill(map, y + 1, x, cub);
	else if (map[y - 1][x] != 1)
		flood_fill(map, y - 1, x, cub);
}

void		ft_pars_map2(t_cub *cub)
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
		while (map[y][x] && map[y][x] != 'N' && map[y][x] != 'W' && map[y][x] != 'E' &&
			map[y][x] != 'S')
				x++;
		if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E' || map[y][x] == 'S')
			break ;
		y++;
	}
	write(1, "a", 1);
	flood_fill(map, x, y, cub);
	write(1, "a", 1);
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
		free(cub->map);
		cub->map = tmp;
		free(line);
	}
	if (close(fd) == -1)
		ft_exit_error("'Close' failed", NULL, cub, 0);
	if (ft_check_char_map(cub->map))
		ft_exit_error("Parsing: Wrong char in map", NULL, cub, 0);
	ft_pars_map2(cub);
}

