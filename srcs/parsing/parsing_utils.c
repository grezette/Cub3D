#include "../../include/cub3d.h"

char	**ft_square_free(char **tab)
{
		int i;

			i = -1;
				while (tab[++i])
							free(tab[i]);
					free(tab);
						return (NULL);
}

int		ft_is_parsing_finished(t_cub *cub)
{
	if (cub->reso.x == -1)
		return (0);
	if (!cub->n_txtr || !cub->s_txtr || !cub->w_txtr || !cub->e_txtr ||
			!cub->spt_txtr)
		return (0);
	if (cub->floor.red == -1 || cub->ceiling.red == -1)
		return (0);
	return (1);
}

int		ft_is_parsing_ok(t_cub *cub)
{
	if (!ft_is_parsing_finished(cub))
		return (-1);
	if (cub->floor.red > 255 || cub->floor.green > 255 ||
			cub->floor.blue > 255 || cub->ceiling.red > 255 ||
			cub->ceiling.green > 255 || cub->ceiling.blue > 255)
		return (-1);
	cub->reso.x = (cub->reso.x > WIDTH_MAX) ? WIDTH_MAX : cub->reso.x;
	cub->reso.y = (cub->reso.x > HEIGHT_MAX) ? HEIGHT_MAX : cub->reso.y;
	return (0);
}

void	ft_pars_init(t_cub *cub)
{
	cub->reso.x = -1;
	cub->n_txtr = NULL;
	cub->s_txtr = NULL;
	cub->w_txtr = NULL;
	cub->e_txtr = NULL;
	cub->spt_txtr = NULL;
	cub->floor.red = -1;
	cub->floor.green = 0;
	cub->floor.blue = 0;
	cub->ceiling.red = -1;
	cub->ceiling.green = 0;
	cub->ceiling.blue = 0;
	cub->map = NULL;
}
