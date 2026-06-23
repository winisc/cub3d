/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 23:17:18 by wini              #+#    #+#             */
/*   Updated: 2026/06/23 10:42:34 by wini             ###   ########.fr       */
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

void	rotate_player(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	move_player(t_player *player, float cos_angle, float sin_angle)
{
	// printf("p.x = %f, p.y = %f\n",  player->pos.x, player->pos.y);
	// printf("cos %f\n", cos_angle);
	// printf("sin %f\n", sin_angle);
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
		player->pos.x += sin_angle * SPEED;
		player->pos.y -= cos_angle * SPEED;
	}
	if (player->key_right == 1)
	{
		player->pos.x -= sin_angle * SPEED;
		player->pos.y += cos_angle * SPEED;
	}
}

void	player_controller(t_player *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	rotate_player(player);
	move_player(player, cos_angle, sin_angle);
}
