/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 04:27:48 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/26 14:25:10 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(int i, char type)
{
	int		a;

	if (type == '2')
		g_spr[i].img =
		mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.s, &a, &a);
	else if (type == '3')
		g_spr[i].img =
		mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.s1, &a, &a);
	else if (type == '4')
		g_spr[i].img =
		mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.s2, &a, &a);
	if (!g_spr[i].img && write(2, "sprite error", 12))
		byebye();
	g_spr[i].data = (int *)mlx_get_data_addr(g_spr[i].img, &a, &a, &a);
}

void	new_frame(void)
{
	mlx_destroy_image(g_mlx_ptr, g_img.img_ptr);
	g_img.img_ptr = mlx_new_image(g_mlx_ptr, g_game_data.res.width,
		g_game_data.res.height);
	g_img.addr = (int *)mlx_get_data_addr(g_img.img_ptr, &g_img.bpp,
		&g_img.line_length, &g_img.endian);
	render3d();
	sp_sort_dist();
	sprites();
	play_music();
	if (g_argc == 2)
		mlx_put_image_to_window(g_mlx_ptr, g_win_ptr, g_img.img_ptr, 0, 0);
}

int		shadows(unsigned int color, int y, int x)
{
	t_color		old_color;
	float		ratio;

	ratio = 0;
	if (g_type == 1)
		ratio = (g_ray_distance[x] * 100 / g_game_data.res.height / 100.0);
	else if (g_type == 0)
		ratio = (y * 100 / ((g_game_data.res.height / 2)
			+ g_player.view) / 100.0);
	else if (g_type == 2)
		ratio = ((g_game_data.res.height / 2) + g_player.view) / (float)y;
	else if (g_type == 3)
		ratio = g_spr[g_spr_id].distance * 100 / g_game_data.res.width / 100.0;
	(ratio > 1) && (ratio = 1);
	(ratio < 0) && (ratio = 0);
	ratio *= 1;
	old_color.r = (color & 0x00ff0000) >> 16;
	old_color.g = (color & 0x0000ff00) >> 8;
	old_color.b = (color & 0x000000ff);
	return (rgbtoint((1 - ratio) * old_color.r + ratio * 0,
			(1 - ratio) * old_color.g + ratio * 0,
			(1 - ratio) * old_color.b + ratio * 0));
}

void	img_update(int x, int y, int color)
{
	if (x >= 0 && x < g_game_data.res.width && y >= 0
		&& y < g_game_data.res.height)
		g_img.addr[(x + (y * g_game_data.res.width))] = shadows(color, y, x);
}
