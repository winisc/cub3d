/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 23:17:18 by wini              #+#    #+#             */
/*   Updated: 2026/06/22 01:21:44 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player(t_player *player)
{
	player->pos.x = WIDTH / 2;
	player->pos.y = HEIGHT / 2;
	player->angle = PI / 2;

	player->key_up = 0;
	player->key_down = 0;
	player->key_left = 0;
	player->key_right = 0;

	player->left_rotate = 0;
	player->right_rotate = 0;
	player->debug = DEBUG;
}

int	key_press(int keycode, t_player *player)
{
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
	if (keycode == C)
		player->debug = !player->debug;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
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

void	move_player(t_player *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;

	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	if (player->key_up == 1)
	{
		player->pos.x += cos_angle * SPEED;
		player->pos.y += sin_angle * SPEED;
	}
	if (player->key_down == 1)
	{
		player->pos.x -= cos_angle * SPEED;
		player->pos.y -= sin_angle * SPEED;
	}
	if (player->key_left == 1)
	{
		player->pos.x += cos_angle * SPEED;
		player->pos.y -= sin_angle * SPEED;
	}
	if (player->key_right == 1)
	{
		player->pos.x -= cos_angle * SPEED;
		player->pos.y += sin_angle * SPEED;
	}
}
