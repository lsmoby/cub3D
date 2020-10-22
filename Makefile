# ********************************** NAME *************************************
NAME = cub3D
BONUS = cub3D_BONUS
# *****************************************************************************

# ********************************** SRCS *************************************
SRCS_DIR = ./
SRCS = 	cub3d.c	read_input.c	input_utils1.c	input_utils2.c	input_utils3.c	\
		input_utils4.c	input_utils5.c	store_map.c	event_handler.c				\
		player_movement.c	ray_casting.c	rendering.c							\
		sprite.c	memory_handling.c	save_img.c	ft_split.c					\
		tools.c	tools2.c	tools3.c	tools4.c								\
		mandatory_functions.c mandatory_functions2.c
SRCS_BONUS = 	cub3d.c	read_input.c	input_utils1.c	input_utils2.c			\
		input_utils3.c	input_utils4.c	input_utils5.c	store_map.c				\
		player_movement.c	ray_casting.c	rendering.c							\
		sprite.c	memory_handling.c	save_img.c	ft_split.c					\
		event_handler.c	tools.c	tools2.c	tools3.c	tools4.c				\
		bonus_functions.c	bonus_functions2.c
TOOLS_DIR = tools/
TOOLS =	xexit.c  xmalloc.c														\
		get_next_line.c															\
		get_next_line_utils.c
INCS = cub3d.h	tools/get_next_line.h	 tools/xmalloc.h
# *****************************************************************************

# ********************************** FLAGS ************************************
FLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror
MLXFLAG = -I -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
# *****************************************************************************

# ********************************** OBJS *************************************
OBJS_DIR 	= 	objs/
OBJS_DIR_T 	= 	objs/
OBJ 		= 	$(SRCS:.c=.o)
OBJ_T 		= 	$(TOOLS:.c=.o)
OBJ_BONUS	=	$(SRCS_BONUS:.c=.o)
OBJS_BONUS	= 	$(addprefix $(OBJS_DIR), $(OBJ_BONUS))
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

$(BONUS) : $(OBJS_BONUS)	$(OBJS_T)
	@clang $(FLAGS) -o $(BONUS) $(OBJS_BONUS) $(OBJS_T) $(MLXFLAG)

all: $(NAME)

bonus: $(BONUS)

clean:
	@echo "Cleaning: $(OBJS_DIR)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Cleaning: $(NAME) and $(BONUS)"
	@rm -f $(NAME) $(BONUS)
	@rm -f screenshot.bmp

re: fclean all
rebonus: fclean bonus
# *****************************************************************************

# START GAME ******************************************************************

launch: re
		@./cub3D map.cub
sslaunch: re
		@./cub3D map.cub --save
bonus_launch: rebonus
		@./cub3D_BONUS map_bonus.cub
bonus_sslaunch: rebonus
		@./cub3D_BONUS map_bonus.cub --save

# *****************************************************************************
