/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:03:21 by wini              #+#    #+#             */
/*   Updated: 2026/07/27 23:08:02 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	mlx_destroy_image(game->mlx, game->img.img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

// void	close_game(t_game *game)
// {
// 	cleanup_game(game);
// 	exit(0);
// 	return (0);	
// }

int	key_press(int keycode, void *param)
{
	t_player	*player;
	
	player = (t_player *)param;
	if (keycode == W)
		player->key_up = 1;
	if (keycode == S)
		player->key_down = 1;
	if (keycode == A)
		player->key_left = 1;
	if (keycode == D)
		player->key_right = 1;
	if (keycode == LEFT)
		player->left_rotate = 1;
	if (keycode == RIGHT)
		player->right_rotate = 1;
	// if (keycode == KEY_ESCAPE)
	// 	close_game(game);
	if (keycode == C)
		player->debug = !player->debug;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_player	*player;

	player = (t_player *)param;
	if (keycode == W)
		player->key_up = 0;
	if (keycode == S)
		player->key_down = 0;
	if (keycode == A)
		player->key_left = 0;
	if (keycode == D)
		player->key_right = 0;
	if (keycode == LEFT)
		player->left_rotate = 0;
	if (keycode == RIGHT)
		player->right_rotate = 0;
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, KEY_PRESS, KEY_PRESS_MASK, key_press, &game->player);
	mlx_hook(game->win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, &game->player);
	// mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
}