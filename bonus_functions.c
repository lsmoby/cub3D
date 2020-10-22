/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:56:39 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 05:26:28 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	system("afplay music/m.wav &>/dev/null &");
	g_start_time = clock();
	g_win_ptr = mlx_new_window(g_mlx_ptr, g_game_data.res.width,
			g_game_data.res.height, "cub3D");
}

void			byebye(void)
{
	if (g_fre)
		free(g_fre);
	xflush();
	free_sprite();
	system("killall afplay");
	exit(0);
}

void			play_music(void)
{
	clock_t current_time;

	current_time = clock();
	if (((double)(current_time - g_start_time) / (double)CLOCKS_PER_SEC) >= 40)
	{
		system("killall afplay");
		system("afplay music/m.wav &>/dev/null &");
		g_start_time = current_time;
	}
}

void			sp_pos(void)
{
	int i;
	int j;

	i = -1;
	ft_bzero(&g_spr, sizeof(g_spr));
	while ((++i < g_game_data.map.rows) && (j = -1))
		while (++j < g_game_data.map.columns && g_num_spr < NBR_SPR)
			if (g_game_data.map.map[j + (i * g_game_data.map.columns)] == '2' ||
			g_game_data.map.map[j + (i * g_game_data.map.columns)] == '3' ||
			g_game_data.map.map[j + (i * g_game_data.map.columns)] == '4')
			{
				g_spr[g_num_spr].x = j * T_S + T_S / 2;
				g_spr[g_num_spr].y = i * T_S + T_S / 2;
				init_sprite(g_num_spr++,
				g_game_data.map.map[j + (i * g_game_data.map.columns)]);
			}
}

int				check_stuff(char *map, int i, int j, int *p)
{
	if (ft_strchr("NSWE", map[j +
		(i * g_game_data.map.columns)]))
		*p = (*p) + 1;
	if (!ft_strchr(" 01234NSEW", map[j +
		(i * g_game_data.map.columns)]))
		return (1);
	if (ft_strchr("0234NSEW", map[j +
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
