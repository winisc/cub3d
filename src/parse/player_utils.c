/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:35:40 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/06 19:00:30 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_player(char direction)
{
	return (direction == 'N' || direction == 'E'
		|| direction == 'W' || direction == 'S');
}

int	collide_checker(double x, double y, t_game *game)
{
	if (touch((x + (PLAYER_SIZE / 2) - 1) - PLAYER_HITBOX,
			(y + (PLAYER_SIZE / 2) - 1) - PLAYER_HITBOX, game))
		return (1);
	if (touch((x + (PLAYER_SIZE / 2) - 1) - PLAYER_HITBOX,
			(y + (PLAYER_SIZE / 2)) + PLAYER_HITBOX, game))
		return (1);
	if (touch((x + (PLAYER_SIZE / 2)) + PLAYER_HITBOX,
			(y + (PLAYER_SIZE / 2)) + PLAYER_HITBOX, game))
		return (1);
	if (touch((x + (PLAYER_SIZE / 2)) + PLAYER_HITBOX,
			(y + (PLAYER_SIZE / 2) - 1) - PLAYER_HITBOX, game))
		return (1);
	return (0);
}
