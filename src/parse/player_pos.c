/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:53:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/04 18:08:21 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_player(char direction)
{
	return (direction == 'N' || direction == 'E' || direction == 'W' || direction == 'S');
}

void	set_player_dir(t_player *player, char direction)
{
	if (direction == 'N')
		player->angle = 3 * PI / 2;
	else if (direction == 'E')
		player->angle = 2 * PI;
	else if (direction == 'S')
		player->angle = PI / 2;
	else if (direction == 'W')
		player->angle = PI;
}

int	set_player_pos(t_player *player, char direction)
{
	if(player->spawn_set == 1)
	{
		// error_msg("Multiple spawn points detected");
		return (1);
	}
	if (!is_player(direction))
	{
		// error_msg("Player spawn not found");
		return (1);
	}
	player->spawn_set = 1;
	set_player_dir(player, direction);
	return (0);
}