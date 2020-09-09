#	$@ == la cible
#	$< == premiere dependance
#	$^ == toutes les dependances

.SUFFIXES:

NAME			=	Cub3D

LIBFT			=	Libft/libft.a

LIBFT_DIR		=	Libft

MLX			= 	minilibx-linux/libmlx_Linux.a

MLX_DIR			=	minilibx-linux

SRCS			=	./srcs/cub3d.c \
					./srcs/cub3d_utils.c \
					./srcs/cub3d_get_info.c \
					./srcs/parsing/ft_pars_file.c \
					./srcs/parsing/parsing_utils.c \
					./srcs/parsing/ft_pars_map.c \
					./srcs/parsing/printf_parsing.c \
					./srcs/raycaster/ft_raycaster.c \
					./srcs/raycaster/raycaster_utils.c \
					./srcs/raycaster/hooking.c \
					./srcs/raycaster/sprite.c \

OBJS			=	$(SRCS:.c=.o)

RM			= 	rm -rf

INC_PATH		= 	-I./include

CC      		=   gcc

CFLAGS       		=   -Wall -Wextra -Werror -g

LIBS			=	-L./Libft -lft -L./minilibx-linux -lmlx_Linux -lX11 -lbsd -lm -lXext 

all:			$(LIBFT) $(MLX) $(NAME)

$(NAME):		 $(OBJS) 
					$(CC) ${CFLAGS} $^ ${LIBS} -o $@

%.o:			%.c	
				$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT)	:
				make every -C $(LIBFT_DIR)

$(MLX)		:
				make -C $(MLX_DIR)

clean:
				make clean -C $(LIBFT_DIR)
				make clean -C $(MLX_DIR)
				$(RM) $(OBJS)

fclean:			clean
				make fclean -C $(LIBFT_DIR)
				make clean -C $(MLX_DIR)
				$(RM) $(NAME)

re:				fclean all
