/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:24 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/02 15:41:27 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_walls1(char *map, int *i, int *j)
{
	while (*i < g_game_data.map.columns - 1)
	{
		if (map[*i + (*j * g_game_data.map.columns)] == '1')
			(*i)++;
		else
			return (-1);
	}
	while (*j < g_game_data.map.rows - 1)
	{
		if (map[*i + (*j * g_game_data.map.columns)] == '1')
			(*j)++;
		else
			return (-1);
	}
	return (1);
}

int		check_walls2(char *map, int *i, int *j)
{
	while (*i > 0)
	{
		if (map[*i + (*j * g_game_data.map.columns)] == '1')
			(*i)--;
		else
			return (-1);
	}
	while (*j >= 0)
	{
		if (map[*i + (*j * g_game_data.map.columns)] == '1')
			(*j)--;
		else
			return (-1);
	}
	return (1);
}

int		map_check(void)
{
	int		i;
	int		j;
	char	*map;
	int		p;

	i = 0;
	j = 0;
	p = 0;
	map = g_game_data.map.map;
	if (!map)
		return (-1);
	if (((int)ft_strlen(g_game_data.map.map) /
			(float)g_game_data.map.columns) != g_game_data.map.rows)
		return (-1);
	if (check_walls1(map, &i, &j) == -1)
		return (-1);
	if (check_walls2(map, &i, &j) == -1)
		return (-1);
	check_p(map, &p);
	if (check_all(map) == -1)
		return (-1);
	if (p != 1)
		return (-1);
	return (1);
}

int		process_input(char **lines)
{
	if (**lines == 'R' && store_resolution(++(*lines)) == -1)
		return (-1);
	if (**lines == 'F' && store_f(++(*lines)) == -1)
		return (-1);
	if (**lines == 'C' && store_c(++(*lines)) == -1)
		return (-1);
	if (ft_comp(*lines, "NO") && store_no((*lines) + 2) == -1)
		return (-1);
	if (ft_comp(*lines, "SO") && store_so((*lines) + 2) == -1)
		return (-1);
	if (ft_comp(*lines, "WE") && store_we((*lines) + 2) == -1)
		return (-1);
	if (ft_comp(*lines, "EA") && store_ea((*lines) + 2) == -1)
		return (-1);
	if (ft_comp(*lines, "S ") && store_s((*lines) + 2) == -1)
		return (-1);
	return (1);
}

int		set_route(char **lines)
{
	if (!lines)
		return (-1);
	while (lines)
	{
		*lines = skip_blanks(*lines);
		if (process_input(lines) == -1)
			return (-1);
		if ((**lines == '1' || **lines == '0') && map_size(lines))
			if (store_map(&lines) == -1)
				return (-1);
		if (*lines == NULL)
			break ;
		else
			lines++;
	}
	if (g_game_data.check != 0x11111111)
		return (-1);
	if (map_check() == -1)
		return (-1);
	xflush();
	return (1);
}
