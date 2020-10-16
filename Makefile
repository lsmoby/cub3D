# ********************************** NAME *************************************
NAME = cub3D
# *****************************************************************************

# ********************************** SRCS *************************************
SRCS_DIR = ./
SRCS = 	cub3d.c	ft_atoi.c	ft_isdigit.c	ft_split.c	\
		ft_strlcpy.c	ft_strtrim.c	img_updater.c				\
		read_input.c	input_utils1.c	input_utils2.c				\
		input_utils3.c	input_utils4.c	input_utils5.c				\
		save_img.c	sprite.c	tools2.c	tools.c	
TOOLS_DIR = tools/
TOOLS =	xexit.c  xmalloc.c				\
		get_next_line.c							\
		get_next_line_utils.c
INCS = cub3d.h	tools/get_next_line.h	 tools/xmalloc.h
# *****************************************************************************

# ********************************** FLAGS ************************************
FLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror
MLXFLAG = -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lbsd -lm
# *****************************************************************************

# ********************************** OBJS *************************************
OBJS_DIR 	= 	objs/
OBJS_DIR_T 	= 	objs/
OBJ 		= 	$(SRCS:.c=.o)
OBJ_T 		= 	$(TOOLS:.c=.o)
OBJS 		= 	$(addprefix $(OBJS_DIR), $(OBJ))
OBJS_T		=	$(addprefix $(OBJS_DIR_T), $(OBJ_T))
# *****************************************************************************

# ****************************** SUBJECT RELATED ******************************

$(OBJS_DIR)%.o	:	$(SRCS_DIR)%.c $(INCS)
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling : $<"
	@clang $(FLAGS) -c $< -o $@

$(OBJS_DIR_T)%.o	:	$(TOOLS_DIR)%.c $(INCS)
	@mkdir -p $(OBJS_DIR_T)
	@echo "Compiling : $<"
	@clang $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)	$(OBJS_T)
	@clang $(FLAGS) -o $(NAME) $(OBJS) $(OBJS_T) $(MLXFLAG)

all: $(NAME)

clean:
	@echo "Cleaning: $(OBJS_DIR)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Cleaning: $(NAME)"
	@rm -f $(NAME)

re: fclean all
# *****************************************************************************

# START GAME ******************************************************************

launch: re
		@./cub3D map.cub
sslaunch: re
		@./cub3D map.cub --save

# *****************************************************************************
