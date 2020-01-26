#	$@ == la cible
#	$< == premiere dependance
#	$^ == toutes les dependances

.SUFFIXES:

NAME			=	Cub3D

LIBFT			=	Libft/libft.a

LIBFT_DIR		=	Libft

SRCS			=	./srcs/cub3d.c

OBJS			=	$(SRCS:.c=.o)

RM				= 	rm -rf

INC_PATH		= 	-I./includes

CC      		=   gcc

CFLAGS       	=   -Wall -Wextra -Werror -g

LIBS			=	-lmlx -framework OpenGL -framework AppKit -L./libft -lft

all:			$(LIBFT) $(NAME)

$(NAME):		 $(OBJS) 
					$(CC) ${CFLAGS} $^ ${LIBS} -o $@

%.o:			%.c	
				$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT)	:
				make every -C $(LIBFT_DIR)

clean:
				make clean -C $(LIBFT_DIR)
				$(RM) $(OBJS)

fclean:			clean
				make fclean -C $(LIBFT_DIR)
				$(RM) $(NAME)

re:				fclean all
