#include "../include/cub3d.h"

void	ft_exit_error(char *msg, void *elem, t_cub *cub, int fd)
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

void	ft_check_param(int ac, char **av)
{
	if (ac < 2 || ac > 3)
		ft_exit_error("Wrong numer of argument\n", NULL, NULL, 0);
	if (ft_strncmp(&(av[1][ft_strlen(av[1]) - 4]), ".cub", 5))
		ft_exit_error("File is not a '.cub'\n", NULL, NULL, 0);
	if (ac == 3 && ft_strncmp(av[2], "--save", 7))
		ft_exit_error("Did you mean '--save'?\n", NULL, NULL, 0);
}

void	ft_minilibx_init(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->reso.x, \
			cub->reso.y, "Cub3D");
	cub->img_ptr = mlx_new_image(cub->mlx_ptr, cub->reso.x, \
			cub->reso.y);
	cub->data = mlx_get_data_addr(cub->img_ptr, &(cub->bpp), \
			&(cub->size_l), &(cub->endian));
	cub->pos = ft_guess_start_position(cub->map);
	cub->dir = ft_guess_start_direction(cub->map, cub->pos.x, cub->pos.y);
	cub->plane.x = 0.5;
	cub->plane.y = 0.5;
	cub->time = 0;
	cub->oldtime = 0;
	cub->moveSpeed = 0.033 * 5.0;
	cub->rotSpeed = 0.033 * 3.0;
	cub->key[0] = 0;
	cub->key[1] = 0;
	cub->key[2] = 0;
	cub->key[3] = 0;
	cub->key[4] = 0;
	cub->key[5] = 0;
	cub->key[6] = 0;
}
