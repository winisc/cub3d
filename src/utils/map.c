/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:59:12 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/07 14:09:44 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_valid_char(char tile)
{
	return (tile == '1' || tile == '0' || tile == ' ' || is_player(tile));
}

void	free_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

int	check_file_chars(t_game *game)
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

int	validate_map(t_game *game)
{
	if (check_file_chars(game))
		return (1);
	if (pad_map(game))
		return (1);
	return (0);
}
int	map_width(t_game *game)
{
	int	max_width;
	int	y;
	int	len;

	y = 0;
	max_width = 0;
	while (game->map.map[y])
	{
		len = ft_strlen(game->map.map[y]);
		if (len > max_width)
			max_width = len;
		y++;
	}
	return (max_width);
}

int	map_height(t_game *game)
{
	int	y;

	y = 0;
	while (game->map.map[y])
		y++;
	return (y);
}
int	is_header_line(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0
		|| line[0] == '\0');
}
