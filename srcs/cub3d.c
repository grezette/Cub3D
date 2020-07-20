/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:00:08 by grezette          #+#    #+#             */
/*   Updated: 2020/07/20 16:58:02 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_check_param(int ac, char **av)
{
	if (ac < 2 || ac > 3)
		ft_exit_error("Wrong numer of argument\n", NULL, NULL, 0);
	if (ft_strncmp(&(av[1][ft_strlen(av[1]) - 4]), ".cub", 5))
		ft_exit_error("File is not a '.cub'\n", NULL, NULL, 0);
	if (ac == 3 && ft_strncmp(av[2], "--save", 7))
		ft_exit_error("Did you mean '--save'?\n", NULL, NULL, 0);
}

int			main(int ac, char **av)
{
	t_cub cub;

	ft_check_param(ac, av);
	ft_pars_file(&cub, av[1]);
	ft_minilibx_init(&cub);
	mlx_hook(cub.win_ptr, X11_KEY_PRESS, \
			X11_KEY_PRESS_M, &key_hook_press, &cub);
	mlx_hook(cub.win_ptr, X11_KEY_RELEASE, \
			X11_KEY_RELEASE_M, &key_hook_release, &cub);
	mlx_loop_hook(cub.mlx_ptr, &loop_hook, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
