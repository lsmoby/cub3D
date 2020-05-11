
NAME = cub3D

SRC =	cub3d.h		cub3d.c	ft_atoi.c	ft_isdigit.c	ft_split.c	\
		ft_strlcpy.c	ft_strtrim.c	img_updater.c				\
		read_input.c	input_utils1.c	input_utils2.c				\
		input_utils3.c	input_utils4.c	input_utils5.c				\
		save_img.c	sprite.c	tools2.c	tools.c					\
		tools/xexit.c  tools/xmalloc.c  tools/xmalloc.h				\
		tools/get_next_line.c		tools/get_next_line.h			\
		tools/get_next_line_utils.c

OBJ = cub3D

all: $(NAME)

MLXFLAG = -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lbsd -lm

$(NAME):
	clang -Wall -Wextra -Werror -g3 -fsanitize=address $(SRC) $(MLXFLAG)

clean:
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re