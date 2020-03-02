/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:40:45 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/02 15:40:51 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_max_w(char *line)
{
	g_game_data.res.width = ft_atoi2(line);
	g_game_data.res.width = g_game_data.res.width > 2560 ?
			2560 : g_game_data.res.width;
}

void	check_max_h(char *line)
{
	g_game_data.res.height = ft_atoi2(line);
	g_game_data.res.height = g_game_data.res.height > 1440 ?
				1440 : g_game_data.res.height;
}

int		store_resolution(char *line)
{
	int x;

	x = g_game_data.check;
	if ((x = (x & 0x00000001)) && (x == 0x00000001))
		return (-1);
	line = skip_blanks(line);
	if (ft_isdigit(*line) && (g_game_data.check =
		(g_game_data.check | 0x00000001)))
	{
		check_max_w(line);
		skip_digits(&line);
		line = skip_blanks(line);
		if (ft_isdigit(*line))
			check_max_h(line);
		else
			return (-1);
	}
	else
		return (-1);
	skip_digits(&line);
	line = skip_blanks(line);
	if (!ft_strchr("\n \t\0", *line))
		return (-1);
	return (1);
}

int		fill_f(char **line)
{
	if (ft_isdigit(**line))
		g_game_data.f.r = ft_atoi(*line);
	else
		return (-1);
	if (!(g_game_data.f.r <= 255 && g_game_data.f.r >= 0))
		return (-1);
	skip_digits2(&line);
	if (**line == ',' && (++(*line)) && ft_isdigit(**line))
		g_game_data.f.g = ft_atoi(*line);
	else
		return (-1);
	if (!(g_game_data.f.g <= 255 && g_game_data.f.g >= 0))
		return (-1);
	skip_digits2(&line);
	if (**line == ',' && (++(*line)) && ft_isdigit(**line))
		g_game_data.f.b = ft_atoi(*line);
	else
		return (-1);
	if (!(g_game_data.f.b <= 255 && g_game_data.f.b >= 0))
		return (-1);
	skip_digits2(&line);
	g_game_data.check = g_game_data.check | 0x00000010;
	return (1);
}

int		store_f(char *line)
{
	int x;
	int ret;

	ret = 1;
	x = g_game_data.check;
	if ((x = (x & 0x00000010)) && (x == 0x00000010))
		return (-1);
	line = skip_blanks(line);
	ret = fill_f(&line);
	line = skip_blanks(line);
	if (!ft_strchr("\n \t\0", *line))
		return (-1);
	return (ret);
}
