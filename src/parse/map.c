/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 20:36:19 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/14 14:30:58 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_width(t_game *game)
{
	int	y;
	int	width;
	int	len;

	y = 0;
	width = 0;
	while (game->map.map[y])
	{
		len = ft_strlen(game->map.map[y]);
		if (len > width)
			width = len;
		y++;
	}
	return (width);
}

int	map_height(t_game *game)
{
	int	y;

	y = 0;
	while (game->map.map[y])
		y++;
	return (y);
}

static int	flood_fill(t_game *game, char **visited, int y, int x)
{
	char	tile;

	tile = get_tile(game, y, x);
	if (tile == ' ')
		return (1);
	if (tile == '1' || is_visited(visited, y, x))
		return (0);
	visited[y][x] = 'V';
	if (flood_fill(game, visited, y - 1, x))
		return (1);
	if (flood_fill(game, visited, y + 1, x))
		return (1);
	if (flood_fill(game, visited, y, x - 1))
		return (1);
	if (flood_fill(game, visited, y, x + 1))
		return (1);
	return (0);
}

int	validate_map_flood(t_game *game)
{
	char	**visited;
	int		start_x;
	int		start_y;
	int		leak;

	game->map.height = map_height(game);
	game->map.width = map_width(game);
	start_x = (int)(game->player.pos.x / BLOCK);
	start_y = (int)(game->player.pos.y / BLOCK);
	visited = alloc_visited(game);
	if (!visited)
		return (error_msg("Error\nMalloc failed\n"));
	leak = flood_fill(game, visited, start_y, start_x);
	free_visited(visited, game->map.height);
	if (leak)
		return (error_msg("Error\nMap is not enclosed\n"));
	return (0);
}
