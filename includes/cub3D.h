/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:17:39 by wini              #+#    #+#             */
/*   Updated: 2026/07/31 21:14:56 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <sys/time.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define DEBUG 1
# define GAME_NAME "CUBO3D"

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define C 99

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK 1
# define KEY_RELEASE_MASK 2

# define DESTROY_WINDOW 17
# define DESTROY_WINDOW_MASK 0
# define KEY_ESCAPE 65307

# define PI 3.14159265350

# define SPEED 200
# define ANGLE_SPEED 4
# define PLAYER_HITBOX 5

typedef struct s_point
{
	float	x;					/* movement speed (horizontal) */
	float	y;					/* movement speed (vertical) */
}	t_point;

typedef struct s_player
{
	t_point	pos;
	float	angle;				/* dir_x or dir_y */
	int		key_up;				/* W -> move up */
	int		key_down;			/* S -> move down */
	int		key_strafe_left;	/* A -> move left */
	int		key_strafe_right;	/* D -> move right */
	int		key_left_rotate;	/* left arrow key */
	int		key_right_rotate;	/* right arrow key */
	int		debug;				/* minimap view */
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	char	*data;
	int		endian;
	int		bpp;
	int		line_len;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	t_img		no;
	t_img		ea;
	t_img		so;
	t_img		we;
	char		*no_path;
	char		*ea_path;
	char		*so_path;
	char		*we_path;
	int			floor_color;
	int			ceiling_color;
	char		*map[500][500];
	char		*path;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	double		last_frame_time;
	t_player	player;
	t_img		img;
}	t_game;

/* game.c */
void	start_game(t_game *game, char *map_file);

/* events.c */
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
void	setup_hooks(t_game *game);
void	cleanup_game(t_game *game);
int		close_game(t_game *game);

/* player.c */
void	rotate_player(t_game *game, double delta_time);
void	move_player(t_game *game, float cos_angle, float sin_angle, double delta_time);
void	player_controller(t_game *game);

/* init.c */
void	init_img(t_img *img);
void	init_player(t_player *player);

/* map.c */
char	**get_map(char *map_file);
void	draw_map(t_game *game);

/* draw.c */
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_square(t_point pos, int size, int color, t_game *game);
void	draw_wall(t_game *game, int column, float height);
void	clear_image(t_game *game);

/* raycast.c */
int		touch(float px, float py, t_game *game);
t_point	cast_ray(t_game *game, t_point start, float ray_angle);
float	wall_height(float dist);
float	ray_distance(t_player *player, t_game *game, float ray_angle);

/* math_utils.c */
float	distance(float x, float y);
float	fixed_dist(t_point pos1, t_point pos2, t_game *game);
double	get_time_seconds(void);
double	compute_delta_time(t_game *game);

/* render.c */
void	render_minimap_view(t_game *game, t_player *player);
void	cast_rays(t_player *player, t_game *game);
int		draw_loop(void *param);

/* textures.c */

#endif
