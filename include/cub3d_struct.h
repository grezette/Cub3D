#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef struct	s_reso
{
		int 	x;
		int 	y;
}				t_reso;

typedef	struct	s_coord
{
		double	x;
		double	y;
}				t_coord;

typedef struct	s_color
{
		int	red;
		int	green;
		int blue;
}				t_color;

typedef struct	s_cub
{
		/*.cub info*/
		t_reso	 reso;
		char	*n_txtr;
		char	*s_txtr;
		char	*w_txtr;
		char	*e_txtr;
		char	*spt_txtr;
		t_color	floor;
		t_color	ceiling;
		char	**map;

		/*mlx info*/
		void	*mlx_ptr;
		void	*win_ptr;
		char	key[6];

		/*img info*/
		void	*img_ptr;
		char		*data;
		int		size_l;
		int		bpp;
		int		endian;

		/*player POV*/
		t_coord	pos;
		t_coord	dir;
		t_coord	plane;

		/*time stuff*/
		double	time;
		double	oldtime;

		/*ray position and direction*/
		double	cameraX;
		t_coord	rayDir;

		/*which box of the map we're in*/
		t_reso	w_map;

		/*lenght of ray from current position to next x or y-side*/
		t_coord	sideDist;

		/*lenght of ray from one x or y-side to next x or y-side*/
		t_coord	deltaDist;
		double	perpWallDist;

		/*what direction to step in x or y-direction (either +1 or -1)*/
		t_reso	step;

		int	hit;
		int	side;

		/*Calculating height stuff*/
		int	lineHeight;

		int	drawStart;
		int	drawEnd;
}				t_cub;

#endif
