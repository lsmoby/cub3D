/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:45:18 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 16:45:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sp_pos(void)
{
	int i;
	int j:

	i = -1;
	g_num_spr = 0;
	while (++i < g_game_data.map.rows && j = -1)
		while (++j < g_game_data.map.columns)
			if (g_game_data.map.map[j + (i * g_game_data.map.columns)] == '2')
			{
				g_spr[g_num_spr].x = j * T_S + T_S / 2;
				g_spr[g_num_spr].y = i * T_S + T_S / 2;
				g_num_spr++;
			}
}

void    sp_sort_dist(void)
{
	int	i;
	int	j;
	t_sprite tmp;

	i = -1;
	while (++i < g_num_spr)
		g_spr[i].distance = dis_2_points(g_player.x, g_spr[i].x, g_player.y, g_spr[i].y);
	i = -1;
	while (++i < g_num_spr && j = -1)
		while (++j < g_num_spr - i)
			if (g_spr[j].distance < g_spr[j + 1].distance)
			{
				tmp = g_spr[j];
				g_spr[j] = g_spr[j + 1];
				g_spr[j + 1] = tmp;
			}
}

void	init_sprite(int i, int *x_s, int *y_s)
{
	int		a;
	void	*p

	p = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.s, &x_s, &y_s);
	if (!p)
	{
		write(1,"sprite error", 12);
		exit(0);
	}
	g_spr[i].data = (int *)mlx_get_data_addr(p, &a, &a, &a);
}

void	sprites(void)
{
	float	angle;
	float	size;
	float	x;
	float	y;
	int		i;

	i = -1;
	while (++i < g_num_spr)
	{
		angle = atan2(g_spr[i].y - g_player.y, g_spr[i].x - g_player.x);
		while (angle - (g_player.rotation_angle * RAD) > M_PI)
			angle -= 2 * M_PI;
		while (angle - (g_player.rotation_angle * RAD) > M_PI)
			angle += 2 * M_PI;
		size = (g_game_data.res.height > g_game_data.res.width) ?
		(g_game_data.res.height / g_sp[k].distance) * TILE_SIZE :
		(g_game_data.res.width / g_sp[k].distance) * TILE_SIZE;
		y = g_game_data.res.height / 2 - size / 2;
		x = (angle - (g_player.rotation_angle * RAD)) *
				g_game_data.res.width / (FOV_ANGLE * RAD) +
				(g_game_data.res.width / 2 - size / 2);
		render_sp(x, y, size, i);
	}
}

void	render_sp(int x, int y, int size, int i)
{
	int x_s;
	int y_s;
	int i;
	int j;
	int color;

	init_sprite(i, &x_s, int &y_s);
	i = -1;
	while (++i < size)
	{
		if (x + i < 0 || x + i > g_game_data.res.width)
			continue;
		if (g_spr[i].distance >= g_ray_distance[x + i])
			continue;
		j = -1;
		while (++j < size)
		{
			color = g_spr[i].data[x_s * (j * y_s / size) + (i * x_s / size)];
			if (color != 0)
				img_update(x + i, y + j, color);
		}
	}
}