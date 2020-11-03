/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:06:30 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/11/03 03:53:22 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				destroy_window(void)
{
	mlx_destroy_image(g_mlx_ptr, g_img.img_ptr);
	mlx_destroy_window(g_mlx_ptr, g_win_ptr);
	byebye();
	return (0);
}

void			init_game(void)
{
	g_num_rays = g_game_data.res.width;
	g_speed = g_game_data.res.width / (g_game_data.res.width / 12);
	g_mlx_ptr = mlx_init();
	g_img.img_ptr = mlx_new_image(g_mlx_ptr, g_game_data.res.width,
				g_game_data.res.height);
	g_img.addr = (int *)mlx_get_data_addr(g_img.img_ptr, &g_img.bpp,
				&g_img.line_length, &g_img.endian);
}

int				main(int ac, char **av)
{
	if (ac < 2 && write(2, "No .cub file entered\n", 21))
		exit(0);
	if (ac > 3 && write(2, "Too many arguments!\n", 20))
		exit(0);
	if (set_route(read_input(av[1])) == -1 &&
			write(2, "Configuration file error\n", 25))
		byebye();
	check_args(ac, av);
	mlx_hook(g_win_ptr, 2, 1L << 0, key_pressed, (void *)0);
	mlx_hook(g_win_ptr, 3, 1L << 1, key_released, (void *)0);
	mlx_hook(g_win_ptr, 17, 0L, destroy_window, (void *)0);
	mlx_loop_hook(g_mlx_ptr, render_frames, (void *)0);
	mlx_loop(g_mlx_ptr);
	return (0);
}
