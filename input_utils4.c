/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:07 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/10 15:13:27 by ael-ghem         ###   ########.fr       */
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

int		map_size(char **line)
{
	char	**save;
	int		i;

	save = line;
	g_game_data.map.columns = 0;
	g_game_data.map.rows = 1;
	i = 0;
	while (*save)
	{
		i = ft_strlen(*save);
		(i > g_game_data.map.columns) ? g_game_data.map.columns = i : 0;
		g_game_data.map.rows++;
		save++;
	}
	g_game_data.map.columns += 2;
	return (1);
}

int		store_map(char ***line)
{
	char	*tmp;
	char	*fre;
	int		i;
	int j;

	i = 0;
	g_game_data.map.map = (char *)malloc(sizeof(char) * g_game_data.map.columns + 1);
	while (i < g_game_data.map.columns)
		g_game_data.map.map[i++] = ' ';
	g_game_data.map.map[i] = '\0';
	printf("%s", g_game_data.map.map);
	while (**line && (***line == '1' || ***line == ' ' || ***line == '0'))
	{
		i = 0;
		tmp = (char *)malloc(sizeof(char) * g_game_data.map.columns + 1);
		(tmp[i] = ' ') && i++;
		while (***line)
			(tmp[i] = ***line) && i++ && (**line)++;
		while (i < g_game_data.map.columns)
			(tmp[i] = ' ') && i++;
		tmp[g_game_data.map.columns] = '\0';
		printf("%s", tmp);
		fre = g_game_data.map.map;
		g_game_data.map.map = ft_strjoin(g_game_data.map.map, tmp);
		free(fre);
		free(tmp);
		(*line)++;
	}
	i = 0;
	tmp = (char *)malloc(sizeof(char) * g_game_data.map.columns + 1);
	while (i < g_game_data.map.columns)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	fre = g_game_data.map.map;
	g_game_data.map.map = ft_strjoin(g_game_data.map.map, tmp);
	printf("%s", tmp);
	free(fre);
	free(tmp);
	i = 0;
	while (i <= g_game_data.map.rows - 1)
	{
		j = 0;
		while ((j < g_game_data.map.columns))
		{
			if (g_game_data.map.map[j + (i * g_game_data.map.columns)] == '\0')
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}
