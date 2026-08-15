/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:17:39 by wini              #+#    #+#             */
/*   Updated: 2026/08/15 18:15:09 by wsilveir         ###   ########.fr       */
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

# define GAME_NAME "CUBO3D"

# define MINI_TILE 8
# define MINI_RADIUS 10
# define MINI_MARGIN 12
# define MINI_BORDER 3
# define MINI_BG 0x000000
# define MINI_WALL 0xC8C8C8
# define MINI_FLOOR 0x303030
# define MINI_VOID 0x101010
# define MINI_PLAYER 0xFF3030
# define MINI_DIR 0xFFD000

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

# define RED	"\033[0;31m"
# define RESET	"\033[0m"

# define SPEED 200
# define ANGLE_SPEED 2.5
# define PLAYER_SIZE 10
# define PLAYER_HITBOX 5
# define READ_CAP 20

typedef enum s_bool
{
	TRUE,
	FALSE,
}	t_bool;

typedef struct s_pos
{
	float	x;
	float	y;
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
	float		angle;
	int			key_up;
	int			key_down;
	int			key_strafe_left;
	int			key_strafe_right;
	int			key_left_rotate;
	int			key_right_rotate;
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
	int		floor_color_set;
	int		ceiling_color_set;
}	t_colors;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map;
	char		*path;
}	t_map;

typedef struct s_ray
{
	t_pos		hit;
	float		dist;
	float		wall_x;
	int			side;
}	t_ray;

typedef struct s_dda
{
	t_pos		pos;
	t_pos		dir;
	t_pos		delta;
	t_pos		side_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
}	t_dda;

typedef struct s_stack
{
	int	*data;
	int	size;
	int	cap;
}	t_stack;

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
void	init_game_data(t_game *game);
int		init_mlx(t_game *game);
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
int		split_header_and_map(char **lines, char ***header, char ***map);
void	strip_newline(char *line);
int		find_map_start(char **lines);
int		count_range(char **lines, int start, int delimiter);
int		alloc_split(char ***header, char ***map,
			int header_count, int map_count);
void	copy_range(char **dest, char **src, int start, int delimiter);

/* parse -> header*/
int		store_texture(char **dest, char *line, int id_len);
int		parse_rgb(char *line, int *color);
int		has_space_after_id(char *line, int len);
char	*skip_spaces(char *line);
int		parse_component(char **line, int *value);
int		is_blank(const char *line);
int		is_color(char *line, char id);
int		parse_header(char **line, t_texpath *texpath, t_colors *colors);
int		is_header_line(const char *line);
int		is_texture_id(char *line, char *id);

/* parse -> player*/
int		is_player(char direction);
int		set_player_pos(t_player *player, char direction, int x, int y);
void	set_player_dir(t_player *player, char direction);
int		collide_checker(double x, double y, t_game *game);

/* parse -> map*/
int		is_valid_char(char tile);
int		pad_map(t_game *game);
int		find_spawn(t_game *game);
int		parse_map(t_game *game);
int		validate_map_flood(t_game *game);
int		flood_fill(t_game *game, char **visited, int y0, int x0);
char	get_tile(t_game *game, int y, int x);
int		is_visited(char **visited, int y, int x);
char	**alloc_visited(t_game *game);
void	free_visited(char **visited, int height);
int		count_rows(t_game *game);
int		is_walkable(char c);
int		tile_is_space(t_game *game, int y, int x);
int		check_cell_leak(t_game *game, int y, int x);
int		check_walkable_cells(t_game *game, int y);
int		map_height(t_game *game);
int		map_width(t_game *game);
int		check_map_chars(t_game *game);
int		check_map_end(char **lines, int map_start);
int		is_map_line(char *line);
int		is_line_empty(char *line);

/* render */
void	draw_minimap(t_game *game);
int		mini_size(void);
int		mini_left(void);
int		mini_tile_color(t_game *game, int cy, int cx);
void	fill_tile(t_game *game, int sx, int sy, int color);
t_pos	tile_screen(t_game *game, int c, int r);
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_wall(t_game *game, int column, t_img *tex, t_ray ray);
void	draw_background(t_game *game);
void	clear_image(t_game *game);
int		touch(float px, float py, t_game *game);
t_ray	cast_ray(t_game *game, t_pos start, float ray_angle);
float	wall_height(float dist);
void	cast_rays(t_player *player, t_game *game);
int		draw_loop(void *param);
int		load_textures(t_game *game);
int		tex_pixel(t_img *tex, int x, int y);
t_img	*pick_texture(t_game *game, t_ray *ray, float cos_a, float sin_a);

/* utils */
void	destroy_textures(t_game *game);
void	cleanup_game(t_game *game);
float	distance(float x, float y);
float	fixed_dist(t_pos pos1, t_pos pos2, t_game *game);
double	get_time_seconds(void);
double	compute_delta_time(t_game *game);
void	free_lines(char **lines, int count);
void	free_str_array(char **arr);

#endif
