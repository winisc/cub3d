/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 20:36:19 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/11 21:17:05 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3D.h"

int	first_non_space(char *row);
int	valid_neighbor(char c);
int	get_row_len(t_game *game, int y);
int	check_interior_row(t_game *game, int y);
int	validate_map_shape(t_game *game);
char	**parse_map(t_game *game, int fd);
static int	check_border_row(char *row);

int	first_non_space(char *row)
{
	int	x;

	x = 0;
	while (row[x] == ' ')
		x++;
	return (x);
}

int	valid_neighbor(char c)
{
	return (c == '1' || c == ' ');
}

int	get_row_len(t_game *game, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	return (ft_strlen(game->map.map[y]));
}

static int	check_border_row(char *row)
{
	int	x;

	x = first_non_space(row);
	while (row[x])
	{
		if (row[x] != '1' && row[x] != ' ')
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
	int		start;

	row = game->map.map[y];
	start = first_non_space(row);
	if (row[start] == '\0' || row[start] != '1')
		return (1);
	if (row[ft_strlen(row) -1] != '1')
		return (1);
	x = start;
	while (row[x])
	{
		if (check_width_rule(game, y, x))
			return (1);
		if (row[x] == ' ' && check_space_neighbors(game, y, x))
			return (1);
		x++;
	}
	if (game->player.spawn_set == 0)
		return (error_msg("Error\nNo spawn points found\n"));
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
				return (1);
		}
		else if (check_interior_row(game, y))
			return (1);
		y++;
	}
	return (0);
}
