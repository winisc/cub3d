/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:59:12 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/14 14:33:01 by mtakiyos         ###   ########.fr       */
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
				return (error_msg("Error\nInvalid characters\n"));
			x++;
		}
		y++;
	}
	return (0);
}

int	is_line_empty(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\t' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int i;

	i = 0;

	if (is_line_empty(line))
		return (0);
	while (line[i])
	{
		if (!is_valid_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_map_end(char **lines, int map_start)
{
	int	i;
	
	i = map_start;
	while (lines[i])
	{
		if (is_line_empty(lines[i]))
			return (error_msg("Error\nJunk found after map ended\n"));
		i++;
	}
	return (0);
}
