/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:59:12 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/13 21:08:33 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid_neighbor(char c)
{
	return (c == '1' || c == ' ');
}

int	is_walkable(char c)
{
	return (c == '0' || is_player(c));
}

int	tile_is_space(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map.height)
		return (1);
	if (x < 0 || (int)ft_strlen(game->map.map[y]))
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

int	get_row_len(t_game *game, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	return (ft_strlen(game->map.map[y]));
}

int	check_border_row(char *row)
{
	int	x;
	int	start;
	int	end;

	start = first_non_space(row);
	end = ft_strlen(row) - 1;
	while (end >= start && row[end] == ' ')
		end--;
	if (start > end)
		return (1);
	x = start;
	while (x <= end)
	{
		if (row[x] != '1')
			return (1);
		x++;
	}
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
