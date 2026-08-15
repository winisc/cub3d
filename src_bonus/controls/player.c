/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 23:17:18 by wini              #+#    #+#             */
/*   Updated: 2026/08/15 19:00:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	rotate_player(t_game *game, double delta_time)
{
	t_player	*player;

	player = &game->player;
	if (player->key_left_rotate)
		player->angle -= ANGLE_SPEED * delta_time;
	if (player->key_right_rotate)
		player->angle += ANGLE_SPEED * delta_time;
}

static void	is_colliding(double new_x, double new_y, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (!collide_checker(new_x, player->pos.y, game))
		player->pos.x = new_x;
	if (!collide_checker(player->pos.x, new_y, game))
		player->pos.y = new_y;
}

static void	normalize_speed(t_game *game, double delta_time)
{
	t_player	*player;
	double		len;
	double		new_x;
	double		new_y;

	player = &game->player;
	len = distance((float)player->move.move_speed_x,
			(float)player->move.move_speed_y);
	if (len > 0.0)
	{
		player->move.move_speed_x /= len;
		player->move.move_speed_y /= len;
	}
	player->move.move_speed_x *= SPEED * delta_time;
	player->move.move_speed_y *= SPEED * delta_time;
	new_x = player->pos.x + player->move.move_speed_x;
	new_y = player->pos.y + player->move.move_speed_y;
	is_colliding(new_x, new_y, game);
}

void	move_player(t_game *game, double delta_time)
{
	t_player	*player;

	player = &game->player;
	init_player_movement(&game->player);
	if (player->key_up == 1)
	{
		player->move.move_speed_x += player->move.dir_x;
		player->move.move_speed_y += player->move.dir_y;
	}
	if (player->key_down == 1)
	{
		player->move.move_speed_x -= player->move.dir_x;
		player->move.move_speed_y -= player->move.dir_y;
	}
	if (player->key_strafe_left == 1)
	{
		player->move.move_speed_x -= player->move.strafe_x;
		player->move.move_speed_y -= player->move.strafe_y;
	}
	if (player->key_strafe_right == 1)
	{
		player->move.move_speed_x += player->move.strafe_x;
		player->move.move_speed_y += player->move.strafe_y;
	}
	normalize_speed(game, delta_time);
}

void	player_controller(t_game *game)
{
	double	delta_time;

	delta_time = compute_delta_time(game);
	move_player(game, delta_time);
	rotate_player(game, delta_time);
}
