#include "../include/cub3d.h"

int		main(int ac, char **av)
{
	t_cub cub;

	ft_check_param(ac, av);
	ft_pars_file(&cub, av[1]);
	return (0);
}
