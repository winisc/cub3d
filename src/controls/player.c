/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 23:17:18 by wini              #+#    #+#             */
/*   Updated: 2026/07/31 21:16:58 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(t_game *game, double delta_time)
{
	t_player *player = &game->player;
	if (player->key_left_rotate)
		player->angle -= ANGLE_SPEED * delta_time;
	if (player->key_right_rotate)
		player->angle += ANGLE_SPEED * delta_time;
	// if (player->player.angle > 2 * PI)
	// 	player->player.angle = 0;
	// if (player->player.angle < 0)
	// 	player->player.angle = 2 * PI;
}

static int	collide_checker(double x, double y, t_game *game)
{
	if (touch((x + 4) - PLAYER_HITBOX, (y + 4) - PLAYER_HITBOX, game))
		return (1);
	if (touch((x + 4) - PLAYER_HITBOX, (y + 5) + PLAYER_HITBOX, game))
		return (1);
	if (touch((x + 5) + PLAYER_HITBOX, (y + 5) + PLAYER_HITBOX, game))
		return (1);
	if (touch((x + 5) + PLAYER_HITBOX, (y + 4) - PLAYER_HITBOX, game))
		return (1);
	return (0);
}

static void	is_colliding(double new_x, double new_y, t_game *game)
{
	t_player *player = &game->player;
	if (!collide_checker(new_x, player->pos.y, game))
		player->pos.x = new_x;
	if (!collide_checker(player->pos.x, new_y, game))
		player->pos.y = new_y;
}

void	move_player(t_game *game, float cos_angle, float sin_angle, double delta_time)
{
	t_player *player = &game->player;
	double	move_speed_x;
	double	move_speed_y;
	double	strafe_x;
	double	strafe_y;
	double	dir_x;
	double	dir_y;

	move_speed_x = 0.0;
	move_speed_y = 0.0;
	dir_x = cos_angle;
	dir_y = sin_angle;
	strafe_x = -dir_y * 0.66;
	strafe_y = dir_x * 0.66;
	if (player->key_up == 1)
	{
		move_speed_x += dir_x;
		move_speed_y += dir_y;
	}
	if (player->key_down == 1)
	{
		move_speed_x -= dir_x;
		move_speed_y -= dir_y;
	}
	if (player->key_strafe_left == 1)
	{
		move_speed_x -= strafe_x;
		move_speed_y -= strafe_y;
	}
	if (player->key_strafe_right == 1)
	{
		move_speed_x += strafe_x;
		move_speed_y += strafe_y;
	}

	double	len;
	len = distance((float)move_speed_x, (float)move_speed_y);
	if (len > 0.0)
	{
		move_speed_x /= len;
		move_speed_y /= len;
	}
	move_speed_x *= SPEED * delta_time;
	move_speed_y *= SPEED * delta_time;

	double	new_x;
	double	new_y;
	new_x = player->pos.x + move_speed_x;
	new_y = player->pos.y + move_speed_y;
	is_colliding(new_x, new_y, game);
	rotate_player(game, delta_time);
}

void	player_controller(t_game *game)
{
	float	cos_angle;
	float	sin_angle;
	double	delta_time;

	delta_time = compute_delta_time(game);
	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	move_player(game, cos_angle, sin_angle, delta_time);
}
