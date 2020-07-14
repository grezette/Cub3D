#include "../include/cub3d.h"

int		main(int ac, char **av)
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
