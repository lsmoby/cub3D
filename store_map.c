/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:50:41 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 03:02:54 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	last_check(void)
{
	int i;
	int j;

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

static void	store(char ***line)
{
	char	*fre;
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * g_game_data.map.columns + 1);
	(tmp[i] = ' ') && i++;
	while (***line)
		(tmp[i] = ***line) && i++ && (**line)++;
	while (i < g_game_data.map.columns)
		(tmp[i] = ' ') && i++;
	tmp[g_game_data.map.columns] = '\0';
	fre = g_game_data.map.map;
	g_game_data.map.map = ft_strjoin(g_game_data.map.map, tmp);
	free(fre);
	free(tmp);
	(*line)++;
}

int			store_map(char ***line)
{
	char	*tmp;
	char	*fre;
	int		i;

	i = 0;
	g_game_data.map.map =
		(char *)malloc(sizeof(char) * g_game_data.map.columns + 1);
	while (i < g_game_data.map.columns)
		g_game_data.map.map[i++] = ' ';
	g_game_data.map.map[i] = '\0';
	while (**line && (***line == '1' || ***line == ' ' || ***line == '0'))
		store(line);
	i = 0;
	tmp = (char *)malloc(sizeof(char) * g_game_data.map.columns + 1);
	while (i < g_game_data.map.columns)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	fre = g_game_data.map.map;
	g_game_data.map.map = ft_strjoin(g_game_data.map.map, tmp);
	free(fre);
	free(tmp);
	return (last_check());
}
