gcc -Wall -Wextra -Werror -g3 -fsanitize=address -I /usr/local/include *.c */*.c -g3 cub3d.h -L  /usr/local/lib -lmlx -framework OpenGL -framework AppKit && ./a.out map.cub