/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 00:00:00 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mini_tile_color(t_game *game, int cy, int cx)
{
	char	tile;

	tile = get_tile(game, cy, cx);
	if (tile == '1')
		return (MINI_WALL);
	if (tile == ' ' || tile == '\0')
		return (MINI_VOID);
	return (MINI_FLOOR);
}

void	fill_tile(t_game *game, int sx, int sy, int color)
{
	int	x;
	int	y;
	int	bx;

	bx = WIDTH - MINI_SPAN * MINI_TILE - MINI_MARGIN;
	y = -1;
	while (++y < MINI_TILE)
	{
		x = -1;
		while (++x < MINI_TILE)
		{
			if (sx + x >= bx && sx + x < bx + MINI_SPAN * MINI_TILE
				&& sy + y >= MINI_MARGIN
				&& sy + y < MINI_MARGIN + MINI_SPAN * MINI_TILE)
				put_pixel(sx + x, sy + y, color, game);
		}
	}
}

t_pos	tile_screen(t_game *game, int c, int r)
{
	t_pos	s;

	s.x = WIDTH - MINI_MARGIN - MINI_SPAN * MINI_TILE / 2
		+ (c - game->player.pos.x / BLOCK) * MINI_TILE;
	s.y = MINI_MARGIN + MINI_SPAN * MINI_TILE / 2
		+ (r - game->player.pos.y / BLOCK) * MINI_TILE;
	return (s);
}
