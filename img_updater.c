/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_updater.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:58:54 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/11 14:43:13 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		shadows(unsigned int color, int type, int y, int x)
{
	t_color		old_color;
	float		ratio;

	ratio = 0;
	if (type == 1)
		ratio = (g_ray_distance[x] * 100 / g_game_data.res.height / 100.0);
	else if (type == 0)
		ratio = (y * 100 / ((g_game_data.res.height / 2) + g_player.view) / 100.0);
	else if (type == 2)
		ratio = ((g_game_data.res.height / 2) + g_player.view) / (float)y;
	else if (type == 3)
		ratio = g_spr[g_spr_id].distance * 100 / g_game_data.res.width / 100.0;
	(ratio > 1) && (ratio = 1);
	(ratio < 0) && (ratio = 0);
	ratio *= 0;
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
		g_img.addr[(x + (y * g_game_data.res.width))] = shadows(color, g_type, y, x);
}