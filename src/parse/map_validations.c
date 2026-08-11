/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 20:36:19 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/10 21:19:22 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3D.h"

int	parse_file(t_game *game, char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	//if (parse_header(fd, &game->texpath, &game->colors)) //TODO:
	//	return (1);
	game->map.map = parse_map(fd);
	close(fd);
	if (!game->map.map)
		return (1);
	if (find_spawn(game))
		return (1);
	return (0);
}

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
		return (1);
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

