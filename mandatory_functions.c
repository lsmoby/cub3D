/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 04:09:49 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 05:31:24 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			byebye(void)
{
	if (g_fre)
		free(g_fre);
	xflush();
	free_sprite();
	exit(0);
}

void			sp_pos(void)
{
	int i;
	int j;

	i = -1;
	ft_bzero(&g_spr, sizeof(g_spr));
	while ((++i < g_game_data.map.rows) && (j = -1))
		while (++j < g_game_data.map.columns && g_num_spr < NBR_SPR)
			if (g_game_data.map.map[j + (i * g_game_data.map.columns)] == '2')
			{
				g_spr[g_num_spr].x = j * T_S + T_S / 2;
				g_spr[g_num_spr].y = i * T_S + T_S / 2;
				init_sprite(g_num_spr++,
				g_game_data.map.map[j + (i * g_game_data.map.columns)]);
			}
}

void			init_sprite(int i, char type)
{
	int		a;

	if (type == '2')
		g_spr[i].img =
		mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.s, &a, &a);
	if (!g_spr[i].img && write(2, "sprite error", 12))
		exit(0);
	g_spr[i].data = (int *)mlx_get_data_addr(g_spr[i].img, &a, &a, &a);
}

void			new_frame(void)
{
	mlx_destroy_image(g_mlx_ptr, g_img.img_ptr);
	g_img.img_ptr = mlx_new_image(g_mlx_ptr, g_game_data.res.width,
		g_game_data.res.height);
	g_img.addr = (int *)mlx_get_data_addr(g_img.img_ptr, &g_img.bpp,
		&g_img.line_length, &g_img.endian);
	render3d();
	sp_sort_dist();
	sprites();
	if (g_argc == 2)
		mlx_put_image_to_window(g_mlx_ptr, g_win_ptr, g_img.img_ptr, 0, 0);
}

void			img_update(int x, int y, int color)
{
	if (x >= 0 && x < g_game_data.res.width && y >= 0
		&& y < g_game_data.res.height)
		g_img.addr[(x + (y * g_game_data.res.width))] = color;
}
