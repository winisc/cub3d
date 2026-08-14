/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:53:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/14 12:27:35 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	set_player_pos(t_player *player, char direction, int x, int y)
{
	if (player->spawn_set == 1)
		return (error_msg("Error\nMultiple spawn points"));
	if (!is_player(direction))
		return (error_msg("Error\nPlayer spawn not found\n"));
	player->pos.x = x * BLOCK + BLOCK / 2;
	player->pos.y = y * BLOCK + BLOCK / 2;
	set_player_dir(player, direction);
	player->spawn_set = 1;
	return (0);
}

int	find_spawn(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (is_player(game->map.map[y][x]))
			{
				if (set_player_pos(&game->player, game->map.map[y][x], x, y))
					return (1);
			}
			x++;
		}
		y++;
	}
	if (game->player.spawn_set == 0)
		return (error_msg("Error\nPlayer spawn not found\n"));
	return (0);
}
