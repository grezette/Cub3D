/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:13:36 by grezette          #+#    #+#             */
/*   Updated: 2020/08/10 16:59:15 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "../Libft/libft.h"
# include "cub3d_struct.h"

# define WIDTH_MAX 2560
# define HEIGHT_MAX 1440

# define X11_KEY_PRESS          2
# define X11_KEY_PRESS_M        1
# define X11_KEY_RELEASE        3
# define X11_KEY_RELEASE_M      2

/*
**utils and security
*/
void	ft_exit_error(char *msg, void *elem, t_cub *cub, int fd);
void	ft_minilibx_init(t_cub *cub);

/*
**minimap
*/
void	ft_minimap(t_cub *cub);

/*
**parsing
*/
void	ft_pars_file(t_cub *cub, char *file);
void	ft_pars_init(t_cub *cub);
void	ft_pars_map(t_cub *cub, int fd);
char	**ft_square_free(char **tab);
int		ft_is_parsing_finished(t_cub *cub);
int		ft_is_parsing_ok(t_cub *cub);
int		ft_minimap_good_size(char **map);

/*
**print_parsing
*/
void	ft_print_parsing(t_cub *cub);

/*
**raycasting
*/
void	ft_raycaster(t_cub *cub);
void	ft_if_raydir(t_cub *cub);
void	ft_rayt_dda(t_cub *cub);
void	ft_rayt_height(t_cub *cub);
int		ft_guess_orientation(t_cub *cub);
void	ft_sprite_casting(t_cub *cub);

/*
**input gathering
*/
int		loop_hook(void *param);
int		key_hook_press(int keycode, void *param);
int		key_hook_release(int keycode, void *param);

void		ft_get_sprt_info(t_cub *cub);
t_coord		ft_guess_start_position(char **map);
void		ft_set_orientation(t_cub *cub, double diry, double plx, double ply);
void		ft_guess_start_direction(t_cub *cub, int x, int y);
void		ft_get_textures_2(t_cub *cub);
#endif
