/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:17:39 by wini              #+#    #+#             */
/*   Updated: 2026/08/11 21:50:53 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
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
# define ANGLE_SPEED 2.5
# define PLAYER_SIZE 10
# define PLAYER_HITBOX 5
# define READ_CAP 20

typedef enum s_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef struct s_pos
{
	float	x;					/* movement speed (horizontal) */
	float	y;					/* movement speed (vertical) */
}	t_pos;

typedef struct s_move
{
	double		move_speed_x;
	double		move_speed_y;
	double		strafe_x;
	double		strafe_y;
	double		dir_x;
	double		dir_y;
}	t_move;

typedef struct s_player
{
	t_move		move;
	t_pos		pos;
	t_bool		spawn_set;
	float		angle;				/* dir_x or dir_y */
	int			key_up;				/* W -> move up */
	int			key_down;			/* S -> move down */
	int			key_strafe_left;	/* A -> move left */
	int			key_strafe_right;	/* D -> move right */
	int			key_left_rotate;	/* left arrow key */
	int			key_right_rotate;	/* right arrow key */
	int			debug;				/* minimap view */
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

typedef struct s_texpath
{
	char		*no;
	char		*ea;
	char		*so;
	char		*we;
}	t_texpath;

typedef struct s_tex
{
	t_img		no;
	t_img		ea;
	t_img		so;
	t_img		we;
}	t_tex;

typedef struct s_colors
{
	int		floor_color;
	int		ceiling_color;
	t_bool	floor_color_set;
	t_bool	ceiling_color_set;
}	t_colors;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map;
	char		*path;
}	t_map;

typedef struct s_game
{
	t_img		img;
	t_tex		tex;
	t_texpath	texpath;
	t_colors	colors;

	t_map		map;
	
	void		*mlx;
	void		*win;
	double		last_frame_time;
	t_player	player;
}	t_game;

/* main / game */
int		start_game(t_game *game, char *map_file);
int		error_msg(char *msg);

/* controls */
int		close_game(t_game *game);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
void	setup_hooks(t_game *game);
void	rotate_player(t_game *game, double delta_time);
void	move_player(t_game *game, double delta_time);
void	player_controller(t_game *game);

/* inits */
void	init_img(t_img *img);
void	init_texture(t_tex *texture);
void	init_texture_path(t_texpath *texpath);
void	init_colors(t_colors *colors);
void	init_player(t_player *player);
void	init_player_movement(t_player *player);
void	init_map(t_map *map);

/* parse -> file */
char	**read_file(int fd);
int		parse_file(t_game *game, char *map_file);

/* parse -> header*/
char	**parse_header(int fd, t_texpath *texpath, t_colors *colors);

/* parse -> player*/
int		set_player_pos(t_player *player, char direction, int x, int y);
void	set_player_dir(t_player *player, char direction);

/* parse -> map*/
int		pad_map(t_game *game);
int		find_spawn(t_game *game);
int		first_non_space(char *row);
int		valid_neighbor(char c);
int		get_row_len(t_game *game, int y);
int		check_interior_row(t_game *game, int y);
int		validate_map_shape(t_game *game);
char	**parse_map(t_game *game, int fd);

/* render */
char		**get_map(t_game *game, char *map_file);
void	draw_map(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_square(t_pos pos, int size, int color, t_game *game);
void	draw_wall(t_game *game, int column, float height);
void	clear_image(t_game *game);
int		touch(float px, float py, t_game *game);
t_pos	cast_ray(t_game *game, t_pos start, float ray_angle);
float	wall_height(float dist);
float	ray_distance(t_player *player, t_game *game, float ray_angle);
void	render_minimap_view(t_game *game, t_player *player);
void	cast_rays(t_player *player, t_game *game);
int		draw_loop(void *param);

/* utils */
void	cleanup_game(t_game *game);
float	distance(float x, float y);
float	fixed_dist(t_pos pos1, t_pos pos2, t_game *game);
double	get_time_seconds(void);
double	compute_delta_time(t_game *game);
int		is_valid_char(char tile);
void	free_lines(char **lines, int count);
int		check_map_chars(t_game *game);
int		is_header_line(const char *line);
int		map_width(t_game *game);
int		map_height(t_game *game);
int		is_player(char direction);
int		collide_checker(double x, double y, t_game *game);

#endif
