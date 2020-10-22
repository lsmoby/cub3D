/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:20:40 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 03:21:24 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			init_player_pos(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_game_data.map.rows && (j = -1))
	{
		while (++j < g_game_data.map.columns)
		{
			g_player.x = (j + 0.5) * T_S;
			g_player.y = (i + 0.5) * T_S;
			if ((g_game_data.map.map[j + (i * g_game_data.map.columns)] == 'N')
				&& (g_player.rotation_angle = 270))
				return ;
			else if ((g_game_data.map.map[j + (i * g_game_data.map.columns)]
			== 'S') && (g_player.rotation_angle = 90))
				return ;
			else if ((g_game_data.map.map[j + (i * g_game_data.map.columns)]
			== 'E') && (g_player.rotation_angle = 180))
				return ;
			else if ((g_game_data.map.map[j + (i * g_game_data.map.columns)]
			== 'W') && !(g_player.rotation_angle = 0))
				return ;
		}
	}
}

void			move_up(void)
{
	float new_x;
	float new_y;

	new_x = cos(g_player.rotation_angle * RAD) * g_speed;
	new_y = sin(g_player.rotation_angle * RAD) * g_speed;
	if (!iswall(g_player.x + new_x * 4, g_player.y + new_y * 4) &&
	!is_sprite(g_player.x + new_x * 4, g_player.y + new_y * 4))
	{
		g_player.x += new_x;
		g_player.y += new_y;
	}
}

void			move_down(void)
{
	float new_x;
	float new_y;

	new_x = cos(g_player.rotation_angle * RAD) * g_speed;
	new_y = sin(g_player.rotation_angle * RAD) * g_speed;
	if (!iswall(g_player.x - new_x * 4, g_player.y - new_y * 4) &&
	!is_sprite(g_player.x - new_x * 4, g_player.y - new_y * 4))
	{
		g_player.x -= new_x;
		g_player.y -= new_y;
	}
}

void			move_right(void)
{
	float new_x;
	float new_y;

	new_x = cos(g_player.rotation_angle * RAD) * g_speed;
	new_y = sin(g_player.rotation_angle * RAD) * g_speed;
	new_x = cos((g_player.rotation_angle + 90) * RAD) * g_speed;
	new_y = sin((g_player.rotation_angle + 90) * RAD) * g_speed;
	if (!iswall(g_player.x + new_x * 2, g_player.y + new_y * 2) &&
	!is_sprite(g_player.x + new_x * 2, g_player.y + new_y * 2))
	{
		g_player.x += new_x;
		g_player.y += new_y;
	}
}

void			move_left(void)
{
	float new_x;
	float new_y;

	new_x = cos(g_player.rotation_angle * RAD) * g_speed;
	new_y = sin(g_player.rotation_angle * RAD) * g_speed;
	new_x = cos((g_player.rotation_angle + 90) * RAD) * g_speed;
	new_y = sin((g_player.rotation_angle + 90) * RAD) * g_speed;
	if (!iswall(g_player.x - new_x * 2, g_player.y - new_y * 2) &&
	!is_sprite(g_player.x - new_x * 2, g_player.y - new_y * 2))
	{
		g_player.x -= new_x;
		g_player.y -= new_y;
	}
}
