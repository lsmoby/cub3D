/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:45:18 by marvin            #+#    #+#             */
/*   Updated: 2020/11/01 13:48:14 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sp_sort_dist(void)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < g_num_spr)
		g_spr[i].distance = dis_2_points(g_player.x,
			g_player.y, g_spr[i].x, g_spr[i].y);
	i = -1;
	while ((++i < g_num_spr) && (j = -1))
		while (++j < g_num_spr - i)
			if (g_spr[j].distance < g_spr[j + 1].distance)
			{
				tmp = g_spr[j];
				g_spr[j] = g_spr[j + 1];
				g_spr[j + 1] = tmp;
			}
}

void	sprites(void)
{
	float	angle;
	float	size;
	float	x;
	float	y;
	int		id;

	id = -1;
	while (++id < g_num_spr)
	{
		angle = atan2(g_spr[id].y - g_player.y, g_spr[id].x - g_player.x);
		while (angle - (g_player.rotation_angle * RAD) > M_PI)
			angle -= 2 * M_PI;
		while (angle - (g_player.rotation_angle * RAD) < -M_PI)
			angle += 2 * M_PI;
		size = (g_game_data.res.width / g_spr[id].distance) * T_S;
		y = (g_game_data.res.height / 2) - (size / 2);
		x = (angle - RAD_ANGLE(g_player.rotation_angle)) *
		g_game_data.res.width / RAD_ANGLE(FOV_ANGLE) +
				((g_game_data.res.width / 2) - (size / 2));
		render_sp(x, y + g_player.view, size, id);
	}
}

void	render_sp(int x, int y, int size, int id)
{
	int i;
	int j;
	int color;

	i = -1;
	g_type = 3;
	g_spr_id = id;
	while (++i < size)
	{
		if ((x + i < 0) || (x + i > g_game_data.res.width))
			continue;
		if (g_spr[id].distance >= g_ray_distance[x + i])
			continue;
		j = -1;
		while (++j < size)
		{
			color = g_spr[id].data[T_S * (j * T_S / size) + (i * T_S / size)];
			if (color != 0)
				if (((x + i) >= 0 && (x + i) < g_game_data.res.width) &&
					((y + j) >= 0 && (y + j) < g_game_data.res.height))
					img_update(x + i, y + j, color);
		}
	}
}
