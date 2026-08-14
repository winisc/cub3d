/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:15:23 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/05 14:34:25 by mtakiyos         ###   ########.fr       */
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
	player->key_strafe_left = 0;
	player->key_strafe_right = 0;
	player->key_left_rotate = 0;
	player->key_right_rotate = 0;
	player->spawn_set = 0;
	player->debug = DEBUG;
}

void	init_player_movement(t_player *player)
{
	t_move	*move;

	move = &player->move;
	move->move_speed_x = 0.0;
	move->move_speed_y = 0.0;
	move->dir_x = cos(player->angle);
	move->dir_y = sin(player->angle);
	move->strafe_x = -move->dir_y * 0.66;
	move->strafe_y = move->dir_x * 0.66;
}
