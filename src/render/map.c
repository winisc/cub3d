/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 00:19:06 by wini              #+#    #+#             */
/*   Updated: 2026/08/12 16:38:06 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_rect(t_game *game, int px, int py, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINI_TILE)
	{
		x = 0;
		while (x < MINI_TILE)
		{
			put_pixel(px + x, py + y, color, game);
			x++;
		}
		y++;
	}
}

static int	mini_tile_color(t_game *game, int cy, int cx)
{
	char	tile;

	tile = get_tile(game, cy, cx);
	if (tile == '1')
		return (MINI_WALL);
	if (tile == ' ' || tile == '\0')
		return (MINI_VOID);
	return (MINI_FLOOR);
}

static void	draw_mini_dir(t_game *game, int px, int py)
{
	float	c;
	float	s;
	int		k;

	c = cos(game->player.angle);
	s = sin(game->player.angle);
	k = 0;
	while (k < MINI_TILE * 3)
	{
		put_pixel(px + (int)(c * k), py + (int)(s * k), MINI_DIR, game);
		k++;
	}
}

static void	draw_mini_player(t_game *game, int ox, int oy)
{
	float	fx;
	float	fy;
	int		px;
	int		py;

	fx = game->player.pos.x / BLOCK - (int)(game->player.pos.x / BLOCK);
	fy = game->player.pos.y / BLOCK - (int)(game->player.pos.y / BLOCK);
	px = ox + (int)((MINI_RADIUS + fx) * MINI_TILE);
	py = oy + (int)((MINI_RADIUS + fy) * MINI_TILE);
	fill_rect(game, px - MINI_TILE / 2, py - MINI_TILE / 2, MINI_PLAYER);
	draw_mini_dir(game, px, py);
}

void	draw_minimap(t_game *game)
{
	int	i;
	int	j;
	int	ox;
	int	wx;
	int	wy;

	wx = (int)(game->player.pos.x / BLOCK) - MINI_RADIUS;
	wy = (int)(game->player.pos.y / BLOCK) - MINI_RADIUS;
	ox = WIDTH - MINI_SPAN * MINI_TILE - MINI_MARGIN;
	j = -1;
	while (++j < MINI_SPAN)
	{
		i = -1;
		while (++i < MINI_SPAN)
			fill_rect(game, ox + i * MINI_TILE, MINI_MARGIN + j * MINI_TILE,
				mini_tile_color(game, wy + j, wx + i));
	}
	draw_mini_player(game, ox, MINI_MARGIN);
}
