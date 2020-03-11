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

void	img_update(int x, int y, int color)
{
	if (x >= 0 && x < g_game_data.res.width && y >= 0
		&& y < g_game_data.res.height)
		g_img.addr[(x + (y * g_game_data.res.width))] = (int)color;
}
