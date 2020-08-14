/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:00:08 by grezette          #+#    #+#             */
/*   Updated: 2020/08/12 12:10:21 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_exit_error_2(t_cub *cub)
{
	if (cub->scr.img_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->scr.img_ptr);
	if (cub->txtr[0].img_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->txtr[0].img_ptr);
	if (cub->txtr[1].img_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->txtr[1].img_ptr);
	if (cub->txtr[2].img_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->txtr[2].img_ptr);
	if (cub->txtr[3].img_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->txtr[3].img_ptr);
	if (cub->spt_img.img_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->spt_img.img_ptr);
	if (cub->win_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->z_buffer)
		free(cub->z_buffer);
	if (cub->sprt)
		free(cub->sprt);
	if (cub->sprt_order)
		free(cub->sprt_order);
	if (cub->sprt_dist)
		free(cub->sprt_dist);
}

void		ft_exit_error(char *msg, void *elem, t_cub *cub, int fd)
{
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
		ft_square_free(cub->map);
	}
	if (fd)
		if (close(fd) == -1)
			write(1, "'close' failed as well\n", 22);
	if (cub)
		ft_exit_error_2(cub);
	system("leaks Cub3D");
	exit(0);
}

static void	ft_check_param(int ac, char **av)
{
	if (ac < 2 || ac > 3)
		ft_exit_error("Wrong numer of argument\n", NULL, NULL, 0);
	if (ft_strncmp(&(av[1][ft_strlen(av[1]) - 4]), ".cub", 5))
		ft_exit_error("File is not a '.cub'\n", NULL, NULL, 0);
	if (ac == 3 && ft_strncmp(av[2], "--save", 7))
		ft_exit_error("Did you mean '--save'?\n", NULL, NULL, 0);
}

void		ft_draw_header(t_cub *cub, int fd)
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

void			ft_minus_minus_save(t_cub *cub)
{
	int fd;
	int	x;
	int	y;

	y = cub->reso.y;
	if ((fd = open("./test.bmp", O_CREAT | O_RDWR | O_TRUNC)) == -1)
		ft_exit_error("failed to create .bmp\n", NULL, cub, 0);
	ft_raycaster(cub);
	ft_draw_header(cub, fd);
	while (--y >= 0 && (x = -1))
		while (++x < cub->reso.x)
			write(fd, &cub->scr.data[4 * y * cub->reso.x + 4 * x], 4);
	system("chmod 777 test.bmp");
	ft_exit_error("No just kidding\n", NULL, cub, fd);
}

int			main(int ac, char **av)
{
	t_cub cub;

	ft_pars_init(&cub);
	ft_check_param(ac, av);
	ft_pars_file(&cub, av[1]);
	ft_minilibx_init(&cub);
	if (ac == 3)
		ft_minus_minus_save(&cub);
	if (!(cub.win_ptr = mlx_new_window(cub.mlx_ptr,
										cub.reso.x, cub.reso.y, "Cub3D")))
	ft_exit_error("Mlx new window failed\n", NULL, &cub, 0);
	mlx_hook(cub.win_ptr, X11_KEY_PRESS,
			X11_KEY_PRESS_M, &key_hook_press, &cub);
	mlx_hook(cub.win_ptr, X11_KEY_RELEASE,
			X11_KEY_RELEASE_M, &key_hook_release, &cub);
	mlx_loop_hook(cub.mlx_ptr, &loop_hook, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
