/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:17:39 by wini              #+#    #+#             */
/*   Updated: 2026/06/22 19:03:32 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
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

# define PI 3.14159265350

# define SPEED 0.8
# define ANGLE_SPEED 0.01

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_player
{
	t_point	pos;
	float	angle;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		left_rotate;
	int		right_rotate;
	int		debug;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	char		**map;
}	t_game;

/* game.c */
void	init_game(t_game *game, char *map_file);

/* events.c */
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);

/* player.c */
void	init_player(t_player *player);
void	rotate_player(t_player *player);
void	move_player(t_player *player, float cos_angle, float sin_angle);
void	player_controller(t_player *player);

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

/* render.c */
void	render_minimap_view(t_game *game, t_player *player);
void	cast_rays(t_player *player, t_game *game);
int		draw_loop(t_game *game);

#endif
