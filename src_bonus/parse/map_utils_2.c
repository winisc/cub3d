/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:59:12 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 19:00:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_walkable(char c)
{
	return (c == '0' || is_player(c));
}

int	tile_is_space(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map.height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(game->map.map[y]))
		return (1);
	return (game->map.map[y][x] == ' ');
}

int	check_walkable_cells(t_game *game, int y)
{
	char	*row;
	int		x;

	row = game->map.map[y];
	x = 0;
	while (row[x])
	{
		if (is_walkable(row[x]) && check_cell_leak(game, y, x))
			return (1);
		x++;
	}
	return (0);
}

int	check_cell_leak(t_game *game, int y, int x)
{
	if (tile_is_space(game, y - 1, x))
		return (1);
	if (tile_is_space(game, y + 1, x))
		return (1);
	if (tile_is_space(game, y, x - 1))
		return (1);
	if (tile_is_space(game, y, x + 1))
		return (1);
	return (0);
}

int	count_rows(t_game *game)
{
	int	y;

	y = 0;
	while (game->map.map[y])
		y++;
	return (y);
}
