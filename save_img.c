/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:48:11 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 02:48:25 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int		write_header(int fd)
{
	int		header_size;
	int		i;
	int		plane_nbr;

	i = -1;
	plane_nbr = 1;
	header_size = 40;
	write(fd, &header_size, 4);
	write(fd, &g_game_data.res.width, 4);
	write(fd, &g_game_data.res.height, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &g_img.bpp, 2);
	while (++i < 28)
		write(fd, "\0", 1);
	return ((i == 27));
}

static	int		write_data(int fd)
{
	int					y;
	int					x;

	y = g_game_data.res.height;
	while (y--)
	{
		x = g_game_data.res.width;
		while (x--)
			if (write(fd, &(g_img.addr)[(y * g_game_data.res.width) + x], 4)
			< 0)
				return (0);
	}
	return (1);
}

static	void	screen_shot(void)
{
	int				fd;
	int				fd_size;
	int				first_pix_byte;

	first_pix_byte = 14 + 40 + 4;
	fd_size = 14 + 40 + 4 + ((g_game_data.res.height
		* g_game_data.res.width) * 3);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
		S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		perror("error creating image");
	write(fd, "BM", 2);
	write(fd, &fd_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix_byte, 4);
	if (write_header(fd) < 0)
		perror("error filling image header");
	if (!write_data(fd))
		perror("error filling image data");
	close(fd);
}

void			save_img(void)
{
	render_frames();
	screen_shot();
	byebye();
}
