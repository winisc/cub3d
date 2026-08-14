/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 20:36:19 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/13 21:02:04 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3D.h"

int	check_width_rule(t_game *game, int y, int x)
{
	int	len_curr;
	int	len_top;
	int	len_bot;

	len_curr = ft_strlen(game->map.map[y]);
	len_top = get_row_len(game, y - 1);
	len_bot = get_row_len(game, y + 1);
	if (len_curr > len_top && x >= len_top && game->map.map[y][x] != '1')
		return (1);
	if (len_curr > len_bot && x >= len_bot && game->map.map[y][x] != '1')
		return (1);
	return (0);
}

int	check_space_neighbors(t_game *game, int y, int x)
{
	char	*row;
	int		len;

	row = game->map.map[y];
	len = ft_strlen(row);
	if (x > 0 && !valid_neighbor(row[x - 1]))
		return (1);
	if (x + 1 < len && !valid_neighbor(row[x + 1]))
		return (1);
	if (x < get_row_len(game, y - 1) && !valid_neighbor(game->map.map[y - 1][x]))
		return (1);
	if (x < get_row_len(game, y + 1) && !valid_neighbor(game->map.map[y + 1][x]))
		return (1);
	return (0);
}

int	check_interior_row(t_game *game, int y)
{
	char	*row;
	int		x;

	row = game->map.map[y];
	if (is_blank(row[0]))
		return (1);
	if (first_non_space(row) != 0 && row[0] != ' ')
		return (1);
	x = first_non_space(row);
	if (row[x] != '1')
		return (1);
	x = ft_strlen(row) - 1;
	while (x >= 0 && row[x] == ' ')
		x--;
	if (x < 0 || row[x] != '1')
		return (1);
	if (check_walkable_cells(game, y))
		return (1);
	return (0);
}

int	validate_map_shape(t_game *game)
{
	int	y;

	game->map.height = count_rows(game);
	y = 0;
	while (game->map.map[y])
	{
		if (y == 0 || y == game->map.height - 1)
		{
			if (check_border_row(game->map.map[y]))
				return (error_msg("border row\n"));
		}
		else if (check_interior_row(game, y))
			return (error_msg("check interior row\n"));
		y++;
	}
	return (0);
}

int	parse_map(t_game *game)
{
	int i = 0;
	while (game->map.map[i])
	{
		printf("MAP[%d] = %s\n", i, game->map.map[i]);
		i++;
	}
	if (check_map_chars(game))
		return (error_msg("map chars\n"));
	if (validate_map_shape(game))
		return (error_msg("map shape\n"));
	return (0);
}
