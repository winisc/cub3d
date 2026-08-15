/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 20:36:19 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 00:58:29 by mtakiyos         ###   ########.fr       */
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

static int	push(int **stack, int *size, int *cap, int y, int x)
{
	int	*new;

	if (*size >= *cap)
	{
		*cap *= 2;
		new = realloc(*stack, sizeof(int) * (*cap) * 2);
		if (!new)
			return (1);
		*stack = new;
	}
	(*stack)[(*size) * 2] = y;
	(*stack)[(*size) * 2 + 1] = x;
	(*size)++;
	return (0);
}

static int	flood_fill(t_game *game, char **visited, int start_y, int start_x)
{
	int	*stack;
	int	size;
	int	cap;
	int	y;
	int x;

	cap = 1024;
	size = 0;
	stack = malloc(sizeof(int) * cap * 2);
	if (!stack || push(&stack, &size, &cap, start_y, start_x))
		return (free(stack), 1);
	while (size > 0)
	{
		size--;
		y = stack[size * 2];
		x = stack[size * 2 + 1];
		if (get_tile(game, y, x) == ' ' || get_tile(game, y, x) == '\0')
			return (free(stack), 1);
		if (get_tile(game, y, x) == '1' || is_visited(visited, y, x))
			continue ;
		visited[y][x] = 'V';
		if (push(&stack, &size, &cap, y - 1, x)
				|| push(&stack, &size, &cap, y + 1, x)
				|| push(&stack, &size, &cap, y, x + 1)
				|| push(&stack, &size, &cap, y, x - 1))
			return (free(stack), 1);
	}
	return (free(stack), 0);
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
