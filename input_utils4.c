/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:07 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 05:29:44 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		fill_c(char **line)
{
	if (ft_isdigit(**line))
		g_game_data.c.r = ft_atoi(*line);
	else
		return (-1);
	if (!(g_game_data.c.r <= 255 && g_game_data.c.r >= 0))
		return (-1);
	skip_digits2(&line);
	if (**line == ',' && (++(*line)) && ft_isdigit(**line))
		g_game_data.c.g = ft_atoi(*line);
	else
		return (-1);
	if (!(g_game_data.c.g <= 255 && g_game_data.c.g >= 0))
		return (-1);
	skip_digits2(&line);
	if (**line == ',' && (++(*line)) && ft_isdigit(**line))
		g_game_data.c.b = ft_atoi(*line);
	else
		return (-1);
	if (!(g_game_data.c.b <= 255 && g_game_data.c.b >= 0))
		return (-1);
	skip_digits2(&line);
	g_game_data.check = g_game_data.check | 0x00000100;
	return (1);
}

int		store_c(char **line)
{
	int x;

	x = g_game_data.check;
	if ((x = (x & 0x00000100)) && (x == 0x00000100))
		return (-1);
	*line = skip_blanks(*line);
	fill_c(line);
	*line = skip_blanks(*line);
	if (!ft_strchr("\n \t\0", **line))
		return (-1);
	else
		(line)++;
	return (1);
}

int		store_s(char *line)
{
	int x;

	x = g_game_data.check;
	if ((x = (x & 0x10000000)) && (x == 0x10000000))
		return (-1);
	line = skip_blanks(line);
	if (!(g_game_data.paths.s = ft_strtrim(line, " \t")))
		return (-1);
	else
		g_game_data.check = g_game_data.check | 0x10000000;
	return (1);
}

int		store_s1(char *line)
{
	line = skip_blanks(line);
	if (!(g_game_data.paths.s1 = ft_strtrim(line, " \t")))
		return (-1);
	return (1);
}

int		store_s2(char *line)
{
	line = skip_blanks(line);
	if (!(g_game_data.paths.s2 = ft_strtrim(line, " \t")))
		return (-1);
	return (1);
}
