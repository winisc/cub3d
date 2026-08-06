/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:53:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/05 21:16:52 by mtakiyos         ###   ########.fr       */
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

void	set_player_pos(t_player *player, char direction, int x, int y)
{
	//TODO: find somewhere better
	// if(player->spawn_set == 1)
	// {
	// 	ft_putstr_fd("Multiple spawn points detected", 2);
	// 	return ;
	// }
	// if (!is_player(direction))
	// {
	// 	ft_putstr_fd("Player spawn not found", 2);
	// 	return ;
	// }
	player->pos.x = x * BLOCK + BLOCK / 2;
	player->pos.y = y * BLOCK + BLOCK / 2;
	set_player_dir(player, direction);
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
			if(is_player(game->map.map[y][x]) && game->player.spawn_set == 1)
			{
				ft_putstr_fd("Multiple spawn points detected", 2);
				return (1);
			}
			if (is_player(game->map.map[y][x]))
			{
				set_player_pos(&game->player, game->map.map[y][x], x, y);
				game->player.spawn_set = 1;
			}
			x++;
		}
		y++;
	}
	if (game->player.spawn_set == 0)
	{
		ft_putstr_fd("Player spawn not found", 2);
		return (1);
	}
	return (0);
}
