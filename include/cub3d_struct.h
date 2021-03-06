/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 14:01:42 by grezette          #+#    #+#             */
/*   Updated: 2020/09/11 15:41:34 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef struct	s_reso
{
	int			x;
	int			y;
}				t_reso;

typedef	struct	s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef	struct	s_img
{
	void		*img_ptr;
	char		*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			h;
}				t_img;

typedef struct	s_cub
{
	t_reso		reso;
	char		*n_txtr;
	char		*s_txtr;
	char		*w_txtr;
	char		*e_txtr;
	char		*spt_txtr;
	t_color		floor;
	t_color		ceiling;
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		scr;
	t_img		scr_two;
	t_img		txtr[4];
	t_coord		pos;
	t_coord		dir;
	t_coord		plane;
	double		camerax;
	t_coord		raydir;
	t_reso		w_map;
	t_coord		sidedist;
	t_coord		deltadist;
	double		perpwalldist;
	t_reso		step;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			key[8];
	double		movespeed;
	double		rotspeed;
	double		*z_buffer;
	t_img		spt_img;
	t_coord		*sprt;
	int			nb_sprt;
	int			*sprt_order;
	double		*sprt_dist;
	t_coord		spt_pos;
	double		invdet;
	t_coord		transform;
	int			spritescreenx;
	int			vmovescreen;
	int			sprt_height;
	t_reso		spt_drawstart;
	t_reso		spt_drawend;
	int			sprite_width;
}				t_cub;

#endif
