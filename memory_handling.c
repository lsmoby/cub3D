/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:24:04 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 04:14:54 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				fill_texture(void)
{
	void		*tmp;
	int			useless;
	int			a;

	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.no, &a, &a);
	g_textures[0] =
	(unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.so, &a, &a);
	g_textures[1] =
	(unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.ea, &a, &a);
	g_textures[2] =
	(unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.we, &a, &a);
	g_textures[3] =
	(unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	a = -1;
	while (++a < 4)
		if (g_textures[a] == NULL)
			return (0);
	return (1);
}

void			free_texture(void)
{
	int i;

	i = 0;
	while (i < 4)
		free(g_textures[i]);
}

void			free_sprite(void)
{
	while (g_num_spr >= 0)
	{
		free(g_spr[g_num_spr].img);
		free(g_spr[g_num_spr].data);
		g_num_spr--;
	}
}
