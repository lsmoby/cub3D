/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:24 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/10 20:28:38 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_check(void)
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
			if (ft_strchr("NSWE",
			map[j + (i * g_game_data.map.columns)]))
				p++;
			if (!ft_strchr(" 01234NSEW",
			map[j + (i * g_game_data.map.columns)]))
				return (-1);
			if (ft_strchr("0234NSEW", map[j + (i * g_game_data.map.columns)]))
			{
				if (map[j + 1 + (i * g_game_data.map.columns)] == ' ' ||
				map[j - 1 + (i * g_game_data.map.columns)] == ' ' ||
				map[j + ((i + 1) * g_game_data.map.columns)] == ' ' ||
				map[j + ((i - 1) * g_game_data.map.columns)] == ' ')
					return (-1);
			}
			else
			{
				if (map[(j + 1) + ((i + 1) * g_game_data.map.columns)] == '0' ||
				map[(j - 1) + ((i - 1) * g_game_data.map.columns)] == '0'
				|| map[(j + 1) + ((i - 1) * g_game_data.map.columns)] == '0'
				|| map[(j - 1) + ((i + 1) * g_game_data.map.columns)] == '0')
					map[j + (i * g_game_data.map.columns)] = '1';
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		process_input(char **lines)
{
	if (**lines == 'R' && ++(*lines) && store_resolution(lines) == -1)
		return (-1);
	if (**lines == 'F' && ++(*lines) && store_f(lines) == -1)
		return (-1);
	if (**lines == 'C' && ++(*lines) && store_c(lines) == -1)
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
		if (process_input(lines) == -1)
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
	xflush();
	return (1);
}

// int main ()
// {
// 		set_route(read_input("map.cub"));
// 	// int i = 0, j = 0;
// 	// while (i <= g_game_data.map.rows)
// 	// {
// 	// 	j = 0;
// 	// 	while (j <= g_game_data.map.columns)
// 	// 	{
// 	// 		printf("%c", g_game_data.map.map[j + (i * g_game_data.map.columns)]);
// 	// 		j++;
// 	// 	}
// 	// 	printf("%c", '\n');
// 	// 	i++;
// 	// }
// }
