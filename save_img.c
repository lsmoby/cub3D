#include "cub3d.h"

void	save_img(void)
{
	sp_sort_dist();
	render3d();
	sprites();
	screen_shot();
	exit(0);
}

void	int_in_char(unsigned char *str, int value)
{
	int i;

	i = -1;
	while (++i < 4)
		str[i] = (unsigned char)(value >> (i * 8));
}

int		write_header(int fd, unsigned int fd_size)
{
	unsigned char	header[54];
	int				i;

	i = -1;
	while (++i < 54)
		header[i] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_in_char(header + 2, fd_size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_in_char(header + 18, g_game_data.res.width);
	int_in_char(header + 22, -g_game_data.res.height);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (write(fd, header, 54));
}

int		write_data(int fd, unsigned int pad_byte_row)
{
	const unsigned char zeroes[3] = {0, 0, 0};
	int					y;
	int					x;

	y = -1;
	while (++y < g_game_data.res.height)
	{
		x = -1;
		while (++x < g_game_data.res.width)
			if (write(fd, &((int*)g_img.addr)[y * g_game_data.res.width + x], 3)
			< 0)
				return (0);
		if (write(fd, &zeroes, pad_byte_row) < 0)
			return (0);
	}
	return (1);
}

void	screen_shot(void)
{
	int				fd;
	unsigned int	fd_size;
	unsigned int	pxl_byte_row;
	unsigned int	pad_byte_row;

	pxl_byte_row = g_game_data.res.width * 3;
	pad_byte_row = (4 - (pxl_byte_row % 4)) % 4;
	fd_size = 54 + (pxl_byte_row + pad_byte_row) * g_game_data.res.height;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
		S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		perror("error creating image");
	if (write_header(fd, fd_size) < 0)
		perror("error creating image");
	if (!write_data(fd, pad_byte_row))
		perror("error creating image");
	close(fd);
}