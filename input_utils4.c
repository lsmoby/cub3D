/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:07 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/02 15:41:09 by ael-ghem         ###   ########.fr       */
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

int		store_c(char *line)
{
	int x;

	x = g_game_data.check;
	if ((x = (x & 0x00000100)) && (x == 0x00000100))
		return (-1);
	line = skip_blanks(line);
	fill_c(&line);
	line = skip_blanks(line);
	if (!ft_strchr("\n \t\0", *line))
		return (-1);
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

int		map_size(char **line)
{
	char **save;
	char *tmp;

	save = line;
	tmp = *line;
	g_game_data.map.columns = 0;
	g_game_data.map.rows = 0;
	*line = skip_blanks(*line);
	while (*tmp == '1' && tmp++ && (tmp = skip_blanks(tmp)))
		g_game_data.map.columns++;
	while (*save && (*save = skip_blanks(*save)) && **save == '1' && save++)
		g_game_data.map.rows++;
	while (line)
	{
		while (*line)
			if (ft_strchr("\n\t ", **line))
				(*line)++;
			else
				return (-1);
		line++;
	}
	return (1);
}

int		store_map(char ***line)
{
	char *tmp;

	g_game_data.map.map = ft_strdup("");
	while ((**line = skip_blanks(**line)) && **line &&
			(***line == '1' || ***line == '0'))
	{
		tmp = g_game_data.map.map;
		g_game_data.map.map = ft_strjoin(g_game_data.map.map,
							ft_strtrimall(**line, " \t"));
		free(tmp);
		(*line)++;
	}
	while (**line)
	{
		while (***line)
			if (ft_strchr(" \t", ***line) != NULL)
				(***line)++;
			else
				return (-1);
		(**line)++;
	}
	return (1);
}
