/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:58:42 by ael-ghem          #+#    #+#             */
/*   Updated: 2020/10/22 05:10:38 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include "tools/get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <time.h>
# include "tools/xmalloc.h"
# define MALLOC xmalloc
# define FREE xfree
# define FLUSH xflush
# define EXIT xexit
# define RAD M_PI/180
# define T_S 64
# define FOV_ANGLE 60
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define UP_KEY 126
# define DOWN_KEY 125
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define RAD_ANGLE(x) ((x * M_PI) / 180)
# define DEG_ANGLE(x) ((x * 180) / M_PI)
# define NBR_SPR 10000

typedef struct	s_h_ray_data
{
	int		foundhorzwallhit;
	float	horzwallhitx;
	float	horzwallhity;
	float	nexthorztouchx;
	float	nexthorztouchy;
	double	horzhitdistance;
}				t_h_ray_data;

typedef struct	s_v_ray_data
{
	int		foundvertwallhit;
	float	vertwallhitx;
	float	vertwallhity;
	float	nextverttouchx;
	float	nextverttouchy;
	double	verthitdistance;
}				t_v_ray_data;

typedef struct	s_cast_data
{
	float			xhintercept;
	float			yhintercept;
	float			xvintercept;
	float			yvintercept;
	float			xstep;
	float			ystep;
	int				rayup;
	int				raydown;
	int				rayleft;
	int				rayright;
	int				washitvertical;
	int				distance;
	int				wallhitx;
	int				wallhity;
	t_h_ray_data	h_ray_data;
	t_v_ray_data	v_ray_data;
}				t_cast_data;

typedef struct	s_player
{
	int		x;
	int		y;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	int		walk_speed;
	int		turn_speed;
	int		pov_direction;
	int		view;
}				t_player;

typedef	struct	s_res
{
	int height;
	int width;
}				t_res;

typedef	struct	s_paths
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *s;
	char *s1;
	char *s2;
}				t_paths;

typedef	struct	s_map
{
	int		rows;
	int		columns;
	char	*map;
}				t_map;

typedef	struct	s_color
{
	int r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_game_data
{
	int		check;
	t_res	res;
	t_paths paths;
	t_color c;
	t_color f;
	t_map	map;
}				t_game_data;

typedef struct	s_textures
{
	void	*ptr;
	int		width;
	int		height;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_textures;
typedef struct	s_img_data
{
	void		*img_ptr;
	int			*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img_data;
typedef	struct	s_tripdata
{
	float distance;
	float distancepp;
	float wallstripheight;
}				t_rip_data;
typedef	struct	s_sprite
{
	int		*data;
	void	*img;
	float	x;
	float	y;
	float	distance;
}				t_sprite;

void			*g_mlx_ptr;
void			*g_win_ptr;
int				g_num_rays;
t_cast_data		g_ray;
t_player		g_player;
t_game_data		g_game_data;
t_img_data		g_img;
t_rip_data		g_strip;
int				g_ray_distance[5120];
unsigned int	*g_textures[5];
t_sprite		g_spr[NBR_SPR];
int				g_num_spr;
int				g_speed;
char			**g_fre;
double			g_start_time;
int				g_type;
int				g_spr_id;
int				g_argc;

char			*ft_strrchr(const char *s, int c);
void			mlx_img_mod(int x, int y, int color);
int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strdup(const char *str);
char			*ft_strchr(const char *s1, int c);
int				ft_isdigit(int s);
char			**ft_split(char const *str, char c);
int				ft_atoi(const char *ptr);
void			*ft_calloc(size_t n, size_t size);
char			*ft_strtrim(char const *s1, char const *set);
int				has_wall(float x, float y);
int				render_frames(void);
int				destroy_window(void);
int				key_pressed(int key);
int				key_released(int key);
int				rgbtoint(int r, int g, int b);
char			*ft_strchr(const char *s, int c);
void			affect_distance(void);
void			v_ray_inter(float ray_angle);
void			h_ray_inter(float ray_angle);
float			normalise_angle(float angle);
int				ft_strcmp(char *s1, char *s2);
void			set_h(void);
void			set(int flag, int i);
void			xflush(void);
void			*xexit(int x);
void			*ftft(void);
void			ft_putstr(char *str);
void			sprites(void);
void			init_sprite(int i, char type);
int				is_sprite(float x, float y);
void			render_sp(int x, int y, int size, int i);
void			sp_sort_dist(void);
void			sp_pos(void);
int				has_sp(float x, float y);
void			grownd(int x);
void			ceiling(int x);
void			init_stripe(float ray_angle, int k);
void			move_x(float new_x, float new_y);
void			move_y(float new_x, float new_y);
void			set_angle(int i, int j);
void			save(int argc, char **argv);
void			black_img(void);
double			dis_2_points(float x1, float y1, float x2, float y2);
void			render3d(void);
void			check_cub(int argc, char **argv);
char			**affect(char **tmp, char **line, char **buffer);
int				map_check2(char *buffer);
char			*skip_blanks(char *str);
void			skip_digits(char **line);
void			skip_digits2(char ***line);
void			check_max_w(char *line);
int				store_resolution(char **line);
void			check_max_h(char *line);
int				fill_f(char **line);
int				store_f(char **line);
int				store_ea(char *line);
int				store_we(char *line);
int				store_so(char *line);
int				store_no(char *line);
char			*skip_blanks(char *str);
int				store_map(char ***line);
int				map_size(char **line);
int				store_s(char *line);
int				store_s1(char *line);
int				store_s2(char *line);
int				store_c(char **line);
int				fill_c(char **line);
void			check_p(char *map, int *p);
char			*ft_strdup(const char *src);
int				check_all(char *map);
long long		ft_atoi2(const char *ptr);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strtrim(char const *s, char const *set);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			img_update(int x, int y, int color);
int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strdup(const char *str);
char			*ft_strchr(const char *s1, int c);
int				ft_isdigit(int s);
char			**ft_split(char const *str, char c);
int				ft_atoi(const char *ptr);
int				ft_comp(char *str, char *f);
char			*ft_strtrimall(char *s, char *set);
void			*ft_calloc(size_t n, size_t size);
char			*ft_strtrim(char const *s1, char const *set);
void			cast_ray(float angle);
int				iswall(float x, float y);
int				render_frames(void);
int				destroy_window(void);
int				key_pressed(int key);
int				key_released(int key);
void			init_player_pos(void);
int				set_route(char **lines);
char			**read_input(char *file);
int				rgbtoint(int r, int g, int b);
void			cast_2d_rays(void);
void			putstripe(float angle, int j);
void			save_img(void);
void			byebye(void);
void			free_texture(void);
int				fill_texture(void);
void			free_sprite(void);
void			play_music(void);
void			init_game(void);
void			check_args(int ac, char **av);
int				check_stuff(char *map, int i, int j, int *p);
void			h_ray_wall_check(void);
void			h_ray(float angle);
void			v_ray_wall_check(void);
void			v_ray(float angle);
void			cast_ray(float angle);
void			react(float x, float top_pixel, float wallstripheight);
void			move_up(void);
void			move_down(void);
void			move_right(void);
void			move_left(void);
void			new_frame(void);

#endif
