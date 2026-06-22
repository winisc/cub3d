/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:44:14 by wini              #+#    #+#             */
/*   Updated: 2026/06/22 02:16:05 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_point pos, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(pos.x + i, pos.y, color, game);
		put_pixel(pos.x, pos.y + i, color, game);
		put_pixel(pos.x + size, pos.y + i, color, game);
		put_pixel(pos.x + i, pos.y + size, color, game);
		i++;
	}
}

void	draw_map(t_game *game)
{
	char	**map;
	t_point	pos;
	int		x;
	int		y;

	map = game->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				pos.x = x * BLOCK;
				pos.y = y * BLOCK;
				draw_square(pos, BLOCK, 0x0000FF, game);
			}
			x++;
		}
		y++;
	}
}

void	clear_image(t_game *game)
{
	ft_bzero(game->data, game->size_line * HEIGHT);
}

void	init_game(t_game *game, char *map_file)
{
	init_player(&game->player);
	game->map = get_map(map_file);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, GAME_NAME);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

static int	valid_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2), 0);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		return (ft_putstr_fd("Error\nMap file must have a .cub extension\n", 2),
			0);
	return (1);
}

int	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (1);
	return (0);
}
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x = x2 - x1;
	float	delta_y = y2 - y1;
	float	angle = atan2(delta_y, delta_x) - game->player.angle;
	float	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float		ray_x;
	float		ray_y;
	float		cos_angle;
	float		sin_angle;

	ray_x = player->pos.x;
	ray_y = player->pos.y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!touch(ray_x, ray_y, game))
	{
		if (player->debug)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	if (!player->debug)
	{
		// float dist = distance(ray_x - player->pos.x, ray_y - player->pos.y);
		float dist = fixed_dist(player->pos.x, player->pos.y, ray_x, ray_y, game);
		float height = (BLOCK / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 255, game);
			start_y++;
		}
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	int			i;
	float		fraction;
	float		start_x;

	player = &game->player;
	move_player(player);
	clear_image(game);
	if (player->debug)
	{
		draw_square(player->pos, 10, 0x00FF00, game);
		draw_map(game);
	}

	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!valid_args(argc, argv))
		return (1);
	init_game(&game, argv[1]);
	mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, key_press, &game.player);
	mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release,
		&game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
