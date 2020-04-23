/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:06:30 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/03/11 20:58:57 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

int		destroy_window(void)
{
	mlx_destroy_image(g_mlx_ptr, g_img.img_ptr);
	mlx_destroy_window(g_mlx_ptr, g_win_ptr);
	exit(0);
}

float	normalise_angle(float angle)
{
	angle = remainder(angle, 360);
	(angle < 0) ? angle += 360 : 0;
	return ((angle));
}

void	init_player_pos(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_game_data.map.rows)
	{
		j = -1;
		while (++j < g_game_data.map.columns)
		{
			if (g_game_data.map.map[j + (i * g_game_data.map.columns)] == 'N')
			{
				g_player.x = (j + 0.5) * T_S;
				g_player.y = (i + 0.5) * T_S;
				g_player.rotation_angle = 270;
				return ;
			}
			else if (g_game_data.map.map[j + (i * g_game_data.map.columns)] == 'S')
			{
				g_player.x = (j + 0.5) * T_S;
				g_player.y = (i + 0.5) * T_S;
				g_player.rotation_angle = 90;
				return ;
			}
			else if (g_game_data.map.map[j + (i * g_game_data.map.columns)] == 'E')
			{
				g_player.x = (j + 0.5) * T_S;
				g_player.y = (i + 0.5) * T_S;
				g_player.rotation_angle = 180;
				return ;
			}
			else if (g_game_data.map.map[j + (i * g_game_data.map.columns)] == 'W')
			{
				g_player.x = (j + 0.5) * T_S;
				g_player.y = (i + 0.5) * T_S;
				g_player.rotation_angle = 0;
				return ;
			}
		}
	}
}

void	put_character(void)
{
	float	phi;
	float	val;
	int		r;
	float	x;
	float	y;

	val = RAD;
	r = 4;
	while (r >= 0)
	{
		phi = 0;
		while (phi <= 360)
		{
			y = (g_player.y) + (r * sin(phi * val));
			x = (g_player.x) + (r * cos(phi * val));
			if (x >= 0 && x < g_game_data.res.width &&
			y >= 0 && y < g_game_data.res.height)
				img_update(x * g_mini, y * g_mini, 0xff0000);
			phi += 0.1;
		}
		r--;
	}
}

int		iswall(float x, float y)
{
	int	xtemp;
	int	ytemp;

	xtemp = (int)floor(x / T_S);
	ytemp = (int)floor(y / T_S);
	if (xtemp <= g_game_data.map.columns && xtemp >= 0
		&& ytemp <= g_game_data.map.rows && ytemp >= 0)
		return (g_game_data.map.map[xtemp +
			(ytemp * g_game_data.map.columns)] == '1');
	return (0);
}

int		is_sprite(float x, float y)
{
	int	xtemp;
	int	ytemp;

	xtemp = (int)floor(x / T_S);
	ytemp = (int)floor(y / T_S);
	if (xtemp <= g_game_data.map.columns && xtemp >= 0
		&& ytemp <= g_game_data.map.rows && ytemp >= 0)
		return (g_game_data.map.map[xtemp +
		(ytemp * g_game_data.map.columns)] == '2' ||
		g_game_data.map.map[xtemp + (ytemp *
		g_game_data.map.columns)] == '3' ||
		g_game_data.map.map[xtemp + (ytemp *
		g_game_data.map.columns)] == '4');
	return (0);
}


int			key_pressed(int key)
{
	if (key == w_key || key == up_key)
		g_player.walk_direction = 1;
	if (key == s_key || key == down_key)
		g_player.walk_direction = -1;
	if (key == left_key)
		g_player.turn_direction = -1;
	if (key == right_key)
		g_player.turn_direction = 1;
	if (key == a_key)
		g_player.pov_direction = -1;
	if (key == d_key)
		g_player.pov_direction = 1;
	return (0);
}

int			key_released(int key)
{
	if (key == w_key || key == s_key)
		g_player.walk_direction = 0;
	if (key == left_key || key == right_key)
		g_player.turn_direction = 0;
	if (key == a_key || key == d_key)
		g_player.pov_direction = 0;
	return (0);
}

void		black_img(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_game_data.res.width)
	{
		j = 0;
		while (j < g_game_data.res.height)
		{
			if ((j >= 0 && j <= g_game_data.res.height) &&
			(i >= 0 && i <= g_game_data.res.width))
				img_update(i, j, 0x000000);
			j++;
		}
		i++;
	}
}

double		dis_2_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void		h_ray(float angle)
{
	g_ray.h_ray_data.foundhorzwallhit = 0;
	g_ray.h_ray_data.horzwallhitx = 0;
	g_ray.h_ray_data.horzwallhity = 0;
	g_ray.yhintercept = floor(g_player.y / T_S) * T_S;
	(g_ray.raydown) ? g_ray.yhintercept += T_S : 0;
	g_ray.xhintercept = g_player.x +
		(g_ray.yhintercept - g_player.y) / tan(angle);
	g_ray.ystep = T_S;
	g_ray.ystep *= (g_ray.rayup) ? -1 : 1;
	g_ray.xstep = T_S / tan(angle);
	g_ray.xstep *= (g_ray.rayleft && g_ray.xstep > 0) ? -1 : 1;
	g_ray.xstep *= (g_ray.rayright && g_ray.xstep < 0) ? -1 : 1;
	g_ray.h_ray_data.nexthorztouchy = g_ray.yhintercept;
	g_ray.h_ray_data.nexthorztouchx = g_ray.xhintercept;
	(g_ray.rayup) ? g_ray.h_ray_data.nexthorztouchy-- : 0;
	while (g_ray.h_ray_data.nexthorztouchy >= 0 &&
	g_ray.h_ray_data.nexthorztouchy <= g_game_data.map.rows * T_S &&
	g_ray.h_ray_data.nexthorztouchx <= g_game_data.map.columns * T_S &&
	g_ray.h_ray_data.nexthorztouchx >= 0)
	{
		if (iswall(g_ray.h_ray_data.nexthorztouchx,
		g_ray.h_ray_data.nexthorztouchy))
		{
			(g_ray.h_ray_data.foundhorzwallhit = 1);
			g_ray.h_ray_data.horzwallhitx =
			g_ray.h_ray_data.nexthorztouchx;
			g_ray.h_ray_data.horzwallhity = (g_ray.rayup) ?
			++g_ray.h_ray_data.nexthorztouchy :
			g_ray.h_ray_data.nexthorztouchy;
			break ;
		}
		else
		{
			g_ray.h_ray_data.nexthorztouchx += g_ray.xstep;
			g_ray.h_ray_data.nexthorztouchy += g_ray.ystep;
		}
	}
	g_ray.h_ray_data.horzhitdistance = dis_2_points(g_player.x, g_player.y,
	g_ray.h_ray_data.horzwallhitx, g_ray.h_ray_data.horzwallhity);
	if (!g_ray.h_ray_data.foundhorzwallhit)
	{
		g_ray.h_ray_data.horzhitdistance = INT_MAX;
	}
}

void	v_ray(float angle)
{
	g_ray.v_ray_data.foundvertwallhit = 0;
	g_ray.v_ray_data.vertwallhitx = 0;
	g_ray.v_ray_data.vertwallhity = 0;
	g_ray.xvintercept = floor(g_player.x / T_S) * T_S;
	(g_ray.rayright) ? g_ray.xvintercept += T_S : 0;
	g_ray.yvintercept = g_player.y +
		(g_ray.xvintercept - g_player.x) * tan(angle);
	g_ray.xstep = T_S;
	g_ray.xstep *= (g_ray.rayleft) ? -1 : 1;
	g_ray.ystep = T_S * tan(angle);
	g_ray.ystep *= (g_ray.rayup && g_ray.ystep > 0) ? -1 : 1;
	g_ray.ystep *= (g_ray.raydown && g_ray.ystep < 0) ? -1 : 1;
	g_ray.v_ray_data.nextverttouchy = g_ray.yvintercept;
	g_ray.v_ray_data.nextverttouchx = g_ray.xvintercept;
	(g_ray.rayleft) ? g_ray.v_ray_data.nextverttouchx-- : 0;
	while (g_ray.v_ray_data.nextverttouchy >= 0 &&
	g_ray.v_ray_data.nextverttouchy <= g_game_data.map.rows * T_S &&
	g_ray.v_ray_data.nextverttouchx <= g_game_data.map.columns * T_S &&
	g_ray.v_ray_data.nextverttouchx >= 0)
	{
		if (iswall(g_ray.v_ray_data.nextverttouchx,
		g_ray.v_ray_data.nextverttouchy))
		{
			g_ray.v_ray_data.foundvertwallhit = 1;
			g_ray.v_ray_data.vertwallhitx = (g_ray.rayleft) ?
			++g_ray.v_ray_data.nextverttouchx :
			g_ray.v_ray_data.nextverttouchx;
			g_ray.v_ray_data.vertwallhity =
			g_ray.v_ray_data.nextverttouchy;
			break ;
		}
		else
		{
			g_ray.v_ray_data.nextverttouchx += g_ray.xstep;
			g_ray.v_ray_data.nextverttouchy += g_ray.ystep;
		}
	}
	if (!g_ray.v_ray_data.foundvertwallhit)
	{
		g_ray.v_ray_data.verthitdistance = INT_MAX;
		return ;
	}
	g_ray.v_ray_data.verthitdistance = dis_2_points(g_player.x, g_player.y,
	g_ray.v_ray_data.vertwallhitx, g_ray.v_ray_data.vertwallhity);
}

void	cast_ray(float angle)
{
	angle = normalise_angle(angle);
	g_ray.wallhitx = 0;
	g_ray.wallhity = 0;
	g_ray.distance = 0;
	g_ray.raydown = (angle > 0 && angle < 180);
	g_ray.rayup = !g_ray.raydown;
	g_ray.rayleft = (angle > 90 && angle < 270);
	g_ray.rayright = !g_ray.rayleft;
	h_ray(RAD_ANGLE(angle));
	v_ray(RAD_ANGLE(angle));
	g_ray.distance = (g_ray.v_ray_data.verthitdistance >
		g_ray.h_ray_data.horzhitdistance) ?
			g_ray.h_ray_data.horzhitdistance :
			g_ray.v_ray_data.verthitdistance;
	g_ray.washitvertical = (g_ray.v_ray_data.verthitdistance <
		g_ray.h_ray_data.horzhitdistance);
	g_ray.wallhitx = (g_ray.v_ray_data.verthitdistance >
		g_ray.h_ray_data.horzhitdistance) ? g_ray.h_ray_data.horzwallhitx
		: g_ray.v_ray_data.vertwallhitx;
	g_ray.wallhity = (g_ray.v_ray_data.verthitdistance >
		g_ray.h_ray_data.horzhitdistance) ? g_ray.h_ray_data.horzwallhity
		: g_ray.v_ray_data.vertwallhity;
}

void	fill_texture(void)
{
	void		*tmp;
	int			useless;
	int			a;
	int			b;

	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.no, &a, &b);
	g_textures[0] =
	(unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.so, &a, &b);
	g_textures[1] =
	(unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.ea, &a, &b);
	g_textures[2] =
	(unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.we, &a, &b);
	g_textures[3] =
	(unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
}

void	react(float x, float top_pixel, float wallstripheight)
{
	int		y;
	int		xoffset;
	int		yoffset;

	y = 0;
	while (y < top_pixel && (y < g_game_data.res.width))
		img_update(x, y++, rgbtoint(g_game_data.c.r,
			g_game_data.c.g, g_game_data.c.b));
	xoffset = (g_ray.washitvertical) ? ((int)g_ray.wallhity % T_S) :
		((int)g_ray.wallhitx % T_S);
	while (y < top_pixel + wallstripheight && y < g_game_data.res.width)
	{
		yoffset = (y - top_pixel) * ((float)T_S / wallstripheight);
		if (g_ray.rayleft && g_ray.washitvertical)
			img_update(x, y, g_textures[0][(yoffset * T_S) + xoffset]);
		else if (g_ray.rayright && g_ray.washitvertical)
			img_update(x, y, g_textures[1][(yoffset * T_S) + xoffset]);
		else if (g_ray.rayup && !g_ray.washitvertical)
			img_update(x, y, g_textures[2][(yoffset * T_S) + xoffset]);
		else if (g_ray.raydown && !g_ray.washitvertical)
			img_update(x, y, g_textures[3][(yoffset * T_S) + xoffset]);
		else
			img_update(x, y, 0xffffffff);
		y++;
	}
	while (y >= 0 && (y < g_game_data.res.width))
		img_update(x, y++, rgbtoint(g_game_data.f.r,
			g_game_data.f.g, g_game_data.f.b));
}

void	putstripe(float angle, int id)
{
	g_strip.distance = g_ray.distance *
		cos(angle - RAD_ANGLE(g_player.rotation_angle));
	g_strip.distancepp = ((float)g_game_data.res.width / 2) /
		(float)tan(RAD_ANGLE(FOV_ANGLE) / 2);
	g_strip.wallstripheight = (T_S / g_strip.distance) * g_strip.distancepp;
	g_ray_distance[id] = g_ray.distance;
	react(id, (g_game_data.res.height / 2) -
	(g_strip.wallstripheight / 2), g_strip.wallstripheight);
}

void	render3d(void)
{
	float	i;
	int		j;

	j = 0;
	i = g_player.rotation_angle - (FOV_ANGLE / 2);
	while (i < g_player.rotation_angle + (FOV_ANGLE / 2))
	{
		cast_ray(i);
		putstripe(RAD_ANGLE(normalise_angle(i)), j);
		i += (float)FOV_ANGLE / g_num_rays;
		j++;
	}
}

int		render_frames(void)
{
	float new_x;
	float new_y;

	new_x = cos(g_player.rotation_angle * RAD) * 8;
	new_y = sin(g_player.rotation_angle * RAD) * 8;
	if (g_player.walk_direction == 1)
	{
		if (!iswall(g_player.x + new_x * 4, g_player.y + new_y * 4) &&
		!is_sprite(g_player.x + new_x * 4, g_player.y + new_y * 4))
		{
			g_player.x += new_x;
			g_player.y += new_y;
		}
	}
	else if (g_player.walk_direction == -1)
	{
		if (!iswall(g_player.x - new_x * 4, g_player.y - new_y * 4) &&
		!is_sprite(g_player.x - new_x * 4, g_player.y - new_y * 4))
		{
			g_player.x -= new_x;
			g_player.y -= new_y;
		}
	}
	if (g_player.turn_direction == 1)
		g_player.rotation_angle += 2;
	else if (g_player.turn_direction == -1)
		g_player.rotation_angle -= 2;
	if (g_player.pov_direction == 1)
	{
		new_x = cos((g_player.rotation_angle + 90) * RAD) * 8;
		new_y = sin((g_player.rotation_angle + 90) * RAD) * 8;
		if (!iswall(g_player.x + new_x * 2, g_player.y + new_y * 2) &&
		!is_sprite(g_player.x + new_x * 2, g_player.y + new_y * 2))
		{
			g_player.x += new_x;
			g_player.y += new_y;
		}
	}
	else if (g_player.pov_direction == -1)
	{
		new_x = cos((g_player.rotation_angle + 90) * RAD) * 8;
		new_y = sin((g_player.rotation_angle + 90) * RAD) * 8;
		if (!iswall(g_player.x - new_x * 2, g_player.y - new_y * 2) &&
		!is_sprite(g_player.x - new_x * 2, g_player.y - new_y * 2))
		{
			g_player.x -= new_x;
			g_player.y -= new_y;
		}
	}
	mlx_destroy_image(g_mlx_ptr, g_img.img_ptr);
	g_img.img_ptr = mlx_new_image(g_mlx_ptr, g_game_data.res.width, g_game_data.res.height);
	g_img.addr = (int *)mlx_get_data_addr(g_img.img_ptr, &g_img.bpp, &g_img.line_length, &g_img.endian);
	render3d();
	sp_sort_dist();
	sprites();
	//draw_map();
	//put_character();
	mlx_put_image_to_window(g_mlx_ptr, g_win_ptr, g_img.img_ptr, 0, 0);
	//printf("%f: %f, %f\n", g_player.rotation_angle, g_player.x, g_player.y);
	return (0);
}

void	check_args(int ac, char **av)
{
	char *s;

	s = ft_strrchr(av[1], '.');
	if ((ft_strlen(s) != 4 || !ft_comp(s + 1, "cub")) &&
		write(2, "No .cub file extension\n", 23))
		exit(0);
	if (ac == 3)
	{
		if ((ft_strlen(av[2]) != 6 || !ft_comp(av[2], "--save")) &&
		write(2, "Wrong second argument\n", 22))
			exit(0);
		else
		{
			save_img();
			exit(0);
		}
	}
}

void	init_game(void)
{
	g_num_rays = g_game_data.res.width;
	g_mlx_ptr = mlx_init();
	g_win_ptr = mlx_new_window(g_mlx_ptr, g_game_data.res.width,
				g_game_data.res.height, "cub3D");
	g_img.img_ptr = mlx_new_image(g_mlx_ptr, g_game_data.res.width,
				g_game_data.res.height);
	g_img.addr = (int *)mlx_get_data_addr(g_img.img_ptr, &g_img.bpp,
				&g_img.line_length, &g_img.endian);
}
int		main(int ac, char **av)
{
	if (ac < 2 && write(2, "No .cub file entered\n", 21))
		exit(0);
	if (ac > 3 && write(2, "Too many arguments!\n", 20))
		exit(0);
	check_args(ac, av);
	if (set_route(read_input(av[1])) == -1 &&
			write(2, "Configuration file error\n", 25))
		exit(0);
	init_game();
	init_player_pos();
	sp_pos();
	fill_texture();
	mlx_hook(g_win_ptr, 2, 1L<<0, key_pressed, (void *)0);
	mlx_hook(g_win_ptr, 3, 1L<<1, key_released, (void *)0);
	mlx_hook(g_win_ptr, 17, 0L, destroy_window, (void *)0);
	mlx_loop_hook(g_mlx_ptr, render_frames, (void *)0);
	mlx_loop(g_mlx_ptr);
	return (0);
}
