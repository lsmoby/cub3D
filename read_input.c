/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:24 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/11/03 04:57:17 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int		last_check(char **lines)
{
	if (**lines == '\0')
		return (0);
	if ((**lines == '1' || **lines == ' ') && g_game_data.check == 0x11111111)
		return (0);
	else if (!(**lines == 'R' || **lines == 'F' || **lines == 'C' ||
			ft_comp(*lines, "NO ") || ft_comp(*lines, "SO ") ||
			ft_comp(*lines, "WE ") || ft_comp(*lines, "EA ") ||
			ft_comp(*lines, "S ")))
		return (1);
	return (0);
}

int				map_check(void)
{
	int		i;
	int		j;
	char	*map;
	int		p;

	i = 1;
	p = 0;
	map = g_game_data.map.map;
	if (!map)
		return (-1);
	while (i < g_game_data.map.rows)
	{
		j = 1;
		while (j < g_game_data.map.columns - 1)
		{
			if (check_stuff(map, i, j, &p))
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int				process_input(char **lines)
{
	if (**lines == 'R' && ++(*lines) && store_resolution(lines) == -1)
		return (-1);
	else if (**lines == 'F' && ++(*lines) && store_f(lines) == -1)
		return (-1);
	else if (**lines == 'C' && ++(*lines) && store_c(lines) == -1)
		return (-1);
	else if (ft_comp(*lines, "NO ") && store_no((*lines) + 2) == -1)
		return (-1);
	else if (ft_comp(*lines, "SO ") && store_so((*lines) + 2) == -1)
		return (-1);
	else if (ft_comp(*lines, "WE ") && store_we((*lines) + 2) == -1)
		return (-1);
	else if (ft_comp(*lines, "EA ") && store_ea((*lines) + 2) == -1)
		return (-1);
	else if (ft_comp(*lines, "S ") && store_s((*lines) + 2) == -1)
		return (-1);
	else if (ft_comp(*lines, "S1 ") && store_s1((*lines) + 2) == -1)
		return (-1);
	else if (ft_comp(*lines, "S2 ") && store_s2((*lines) + 2) == -1)
		return (-1);
	return (1);
}

int				set_route(char **lines)
{
	if (!lines || !*lines)
		return (-1);
	g_fre = lines;
	while (lines)
	{
		if (process_input(lines) == -1)
			return (-1);
		if (last_check(lines))
			return (-1);
		if ((**lines == '1' || **lines == ' ') && map_size(lines))
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
	return (1);
}
