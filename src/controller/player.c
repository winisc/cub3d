/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 23:17:18 by wini              #+#    #+#             */
/*   Updated: 2026/07/28 16:02:43 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(t_game *player)
{
	if (player->player.left_rotate)
		player->player.angle -= ANGLE_SPEED;
	if (player->player.right_rotate)
		player->player.angle += ANGLE_SPEED;
	if (player->player.angle > 2 * PI)
		player->player.angle = 0;
	if (player->player.angle < 0)
		player->player.angle = 2 * PI;
}

void	move_player(t_game *player, float cos_angle, float sin_angle)
{
	// printf("p.x = %f, p.y = %f\n",  player->player.pos.x, player->player.pos.y);
	// printf("cos %f\n", cos_angle);
	// printf("sin %f\n", sin_angle);
	if (player->player.key_up == 1)
	{
		player->player.pos.x += cos_angle * SPEED;
		player->player.pos.y += sin_angle * SPEED;
	}
	if (player->player.key_down == 1)
	{
		player->player.pos.x -= cos_angle * SPEED;
		player->player.pos.y -= sin_angle * SPEED;
	}
	if (player->player.key_left == 1)
	{
		player->player.pos.x += sin_angle * SPEED;
		player->player.pos.y -= cos_angle * SPEED;
	}
	if (player->player.key_right == 1)
	{
		player->player.pos.x -= sin_angle * SPEED;
		player->player.pos.y += cos_angle * SPEED;
	}
}

void	player_controller(t_game *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->player.angle);
	sin_angle = sin(player->player.angle);
	rotate_player(player);
	move_player(player, cos_angle, sin_angle);
}
