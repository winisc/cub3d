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

/*
** Minimap geometry, all derived from MINI_RADIUS and MINI_TILE:
**   cells across = 2 * MINI_RADIUS + 1  (odd, player sits in the middle)
**   mini_size()  = that many cells in pixels  (the box is a square)
**   mini_left()  = the box left edge, anchored to the top-right corner
*/
int	mini_size(void)
{
	return ((2 * MINI_RADIUS + 1) * MINI_TILE);
}

int	mini_left(void)
{
	return (WIDTH - mini_size() - MINI_MARGIN);
}

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

/* Fills one MINI_TILE square at (sx, sy), clipped to the minimap box. */
void	fill_tile(t_game *game, int sx, int sy, int color)
{
	int	x;
	int	y;
	int	left;
	int	size;

	left = mini_left();
	size = mini_size();
	y = 0;
	while (y < MINI_TILE)
	{
		x = 0;
		while (x < MINI_TILE)
		{
			if (sx + x >= left && sx + x < left + size
				&& sy + y >= MINI_MARGIN && sy + y < MINI_MARGIN + size)
				put_pixel(sx + x, sy + y, color, game);
			x++;
		}
		y++;
	}
}

/* Screen position of map cell (c, r): the grid scrolls under the player,
   who stays at the box center, offset by their sub-cell fraction. */
t_pos	tile_screen(t_game *game, int c, int r)
{
	t_pos	s;
	int		cx;
	int		cy;

	cx = mini_left() + mini_size() / 2;
	cy = MINI_MARGIN + mini_size() / 2;
	s.x = cx + (c - game->player.pos.x / BLOCK) * MINI_TILE;
	s.y = cy + (r - game->player.pos.y / BLOCK) * MINI_TILE;
	return (s);
}
