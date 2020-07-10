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
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->reso.x, cub->reso.y, "Cub3D");
	cub->img_ptr = mlx_new_image(cub->mlx_ptr, cub->reso.x, cub->reso.y);
	cub->data = mlx_get_data_addr(cub->img_ptr, &(cub->bpp), &(cub->size_l), &(cub->endian));
}
