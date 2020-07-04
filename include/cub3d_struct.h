#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

typedef struct	s_coord
{
		int x;
		int y;
}				t_coord;

typedef struct	s_color
{
		int	red;
		int	green;
		int blue;
}				t_color;

typedef struct	s_cub
{
		t_coord reso;
		char	*n_txtr;
		char	*s_txtr;
		char	*w_txtr;
		char	*e_txtr;
		char	*spt_txtr;
		t_color	floor;
		t_color	ceiling;
		char	**map;

}				t_cub;

#endif
