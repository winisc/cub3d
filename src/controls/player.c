/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 23:17:18 by wini              #+#    #+#             */
/*   Updated: 2026/07/30 23:03:51 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(t_game *player)
{
	if (player->player.key_left_rotate)
		player->player.angle -= ANGLE_SPEED;
	if (player->player.key_right_rotate)
		player->player.angle += ANGLE_SPEED;
	// if (player->player.angle > 2 * PI)
	// 	player->player.angle = 0;
	// if (player->player.angle < 0)
	// 	player->player.angle = 2 * PI;
}

int	is_colliding(double x, double y, t_game *game)
{
	if (touch(x - PLAYER_HITBOX, y - PLAYER_HITBOX, game))
		return (1);
	if (touch(x - PLAYER_HITBOX, y + PLAYER_HITBOX, game))
		return (1);
	if (touch(x + PLAYER_HITBOX, y + PLAYER_HITBOX, game))
		return (1);
	if (touch(x + PLAYER_HITBOX, y - PLAYER_HITBOX, game))
		return (1);
	return (0);
}

void	move_player(t_game *game, float cos_angle, float sin_angle)
{
	// printf("p.x = %f, p.y = %f\n",  player->player.pos.x, player->player.pos.y);
	// printf("cos %f\n", cos_angle);
	// printf("sin %f\n", sin_angle);
	t_player *player = &game->player;
	double	len;
	double	move_speed_x;
	double	move_speed_y;
	double	strafe_x;
	double	strafe_y;
	double	dir_x;
	double	dir_y;
	double	new_x;
	double	new_y;

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
	len = sqrt((move_speed_x * move_speed_x) + (move_speed_y * move_speed_y));
	if (len > 0.0)
	{
		move_speed_x /= len;
		move_speed_y /= len;
	}

	move_speed_x *= SPEED;
	move_speed_y *= SPEED;
	new_x = player->pos.x + move_speed_x;
	new_y = player->pos.y + move_speed_y;

	if (!is_colliding(new_x, player->pos.y, game))
		player->pos.x = new_x;
	if (!is_colliding(player->pos.x, new_y, game))
		player->pos.y = new_y;
}

// void	move_player(t_game *player, float cos_angle, float sin_angle)
// {
// 	// printf("p.x = %f, p.y = %f\n",  player->player.pos.x, player->player.pos.y);
// 	// printf("cos %f\n", cos_angle);
// 	// printf("sin %f\n", sin_angle);
// 	if (player->player.key_up == 1)
// 	{
// 		player->player.pos.x += cos_angle * SPEED;
// 		player->player.pos.y += sin_angle * SPEED;
// 	}
// 	if (player->player.key_down == 1)
// 	{
// 		player->player.pos.x -= cos_angle * SPEED;
// 		player->player.pos.y -= sin_angle * SPEED;
// 	}
// 	if (player->player.key_strafe_left == 1)
// 	{
// 		player->player.pos.x += sin_angle * SPEED;
// 		player->player.pos.y -= cos_angle * SPEED;
// 	}
// 	if (player->player.key_strafe_right == 1)
// 	{
// 		player->player.pos.x -= sin_angle * SPEED;
// 		player->player.pos.y += cos_angle * SPEED;
// 	}
// }

void	player_controller(t_game *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->player.angle);
	sin_angle = sin(player->player.angle);
	move_player(player, cos_angle, sin_angle);
	rotate_player(player);
}

// void	draw_debug(t_game *game, double move_x, double move_y)
// {
// 	char	buf[128];
// 	double	len;

// 	len = sqrt(move_x * move_x + move_y * move_y);
// 	snprintf(buf, sizeof(buf), "move_x=%.3f move_y=%.3f len=%.3f",
// 		move_x, move_y, len);
// 	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, buf);
// }

