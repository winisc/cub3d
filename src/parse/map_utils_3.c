/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 20:30:00 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/14 20:30:00 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	get_tile(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map.height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(game->map.map[y]))
		return (' ');
	return (game->map.map[y][x]);
}

int	is_visited(char **visited, int y, int x)
{
	return (visited[y][x] == 'V');
}

char	**alloc_visited(t_game *game)
{
	char	**visited;
	int		y;

	visited = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!visited)
		return (NULL);
	y = 0;
	while (y < game->map.height)
	{
		visited[y] = ft_calloc(game->map.width + 1, sizeof(char));
		if (!visited[y])
		{
			while (y > 0)
				free(visited[--y]);
			free(visited);
			return (NULL);
		}
		y++;
	}
	return (visited);
}

void	free_visited(char **visited, int height)
{
	int	y;

	if (!visited)
		return ;
	y = 0;
	while (y < height)
	{
		free(visited[y]);
		y++;
	}
	free(visited);
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
