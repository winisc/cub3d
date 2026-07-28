/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:03:21 by wini              #+#    #+#             */
/*   Updated: 2026/07/28 18:07:27 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->img.img_ptr && game->mlx)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
	{
		free(game->map);
		game->map = NULL;
	}
}

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return (0);
	if (keycode == W)
		game->player.key_up = 1;
	if (keycode == S)
		game->player.key_down = 1;
	if (keycode == A)
		game->player.key_left = 1;
	if (keycode == D)
		game->player.key_right = 1;
	if (keycode == LEFT)
		game->player.left_rotate = 1;
	if (keycode == RIGHT)
		game->player.right_rotate = 1;
	if (keycode == KEY_ESCAPE)
		close_game(game);
	if (keycode == C)
		game->player.debug = !game->player.debug;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return (0);
	if (keycode == W)
		game->player.key_up = 0;
	if (keycode == S)
		game->player.key_down = 0;
	if (keycode == A)
		game->player.key_left = 0;
	if (keycode == D)
		game->player.key_right = 0;
	if (keycode == LEFT)
		game->player.left_rotate = 0;
	if (keycode == RIGHT)
		game->player.right_rotate = 0;
	return (0);
}

void	setup_hooks(t_game *game)
{
	if (!game || !game->win || !game->mlx)
		return ;
	mlx_hook(game->win, KEY_PRESS, KEY_PRESS_MASK, key_press, game);
	mlx_hook(game->win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
}
