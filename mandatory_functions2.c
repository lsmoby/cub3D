/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_functions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 05:25:09 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 05:25:20 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				check_stuff(char *map, int i, int j, int *p)
{
	if (ft_strchr("NSWE", map[j +
		(i * g_game_data.map.columns)]))
		*p = (*p) + 1;
	if (!ft_strchr(" 012NSEW", map[j +
		(i * g_game_data.map.columns)]))
		return (1);
	if (ft_strchr("02NSEW", map[j +
		(i * g_game_data.map.columns)]))
	{
		if (map[j + 1 + (i * g_game_data.map.columns)] == ' ' ||
		map[j - 1 + (i * g_game_data.map.columns)] == ' ' ||
		map[j + ((i + 1) * g_game_data.map.columns)] == ' ' ||
		map[j + ((i - 1) * g_game_data.map.columns)] == ' ')
			return (1);
	}
	else
	{
		if (map[(j + 1) + ((i + 1) * g_game_data.map.columns)] == '0' ||
		map[(j - 1) + ((i - 1) * g_game_data.map.columns)] == '0'
		|| map[(j + 1) + ((i - 1) * g_game_data.map.columns)] == '0'
		|| map[(j - 1) + ((i + 1) * g_game_data.map.columns)] == '0')
			map[j + (i * g_game_data.map.columns)] = '1';
	}
	return (0);
}

void			check_args(int ac, char **av)
{
	char *s;

	s = ft_strrchr(av[1], '.');
	if ((ft_strlen(s) != 4 || !ft_comp(s + 1, "cub")) &&
		write(2, "No .cub file extension\n", 23))
		exit(0);
	init_game();
	init_player_pos();
	sp_pos();
	if (!fill_texture() && write(2, "error loading textures\n", 22))
		exit(0);
	if ((g_argc = ac) == 3)
	{
		if ((ft_strlen(av[2]) != 6 || !ft_comp(av[2], "--save")) &&
		write(2, "Wrong second argument\n", 22))
			exit(0);
		else
			save_img();
	}
	g_start_time = 0;
	g_win_ptr = mlx_new_window(g_mlx_ptr, g_game_data.res.width,
			g_game_data.res.height, "cub3D");
}
