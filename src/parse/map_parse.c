/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:35:07 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/05 21:31:31 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3D.h"

int	is_valid_char(char tile)
{
	return (tile == '1' || tile == '0' || tile == ' ' || is_player(tile));
}

int	parse_map_lines()
{
	
}

int	check_map_chars(t_game *game)
{
	int	x;
	int	y;
	
	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (!is_valid_char(game->map.map[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	pad_map(t_game *game)
{
	int		y;
	int		width;
	char	*padded;

	width = map_width(game); //TODO:
	y = 0;
	while (game->map.map[y])
	{
		padded = ft_calloc(width + 1, sizeof(char));
		if (!padded)
			return (1);
		ft_memset(padded, ' ', width);
		ft_strlcpy(padded, game->map.map[y], ft_strlen(game->map.map[y]));
		free(game->map.map[y]);
		game->map.map[y] = padded;
		y++;
	}
	game->colors.width = width;
	game->colors.height = map_height(game); //TODO:
	return (0);
}

int	validate_map(t_game *game)
{
	if (check_map_chars(game))
		return (1);
	if (pad_map(game))
		return (1);
	return (0);
}

int	parse_map_file(t_game *game, char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1); //TODO
	if (!parse_header(fd, &game->texpath, &game->colors)) //TODO:
		return (1);
	game->map.map = parse_map_lines(fd); //TODO:
	close(fd);
	if (!game->map.map)
		return (1);
	// if (validate_map(game))
	// 	return (1);
	if (find_spawn(game))
		return (1);
	// if (is_enclosed(game)) //TODO:
	// 	return (1);
	return (0);
}
