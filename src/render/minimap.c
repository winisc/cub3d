/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 00:00:00 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	mini_bg(t_game *game)
{
	int	x;
	int	y;
	int	bx;
	int	by;

	bx = WIDTH - MINI_SPAN * MINI_TILE - MINI_MARGIN - MINI_BORDER;
	by = MINI_MARGIN - MINI_BORDER;
	y = -1;
	while (++y < MINI_SPAN * MINI_TILE + 2 * MINI_BORDER)
	{
		x = -1;
		while (++x < MINI_SPAN * MINI_TILE + 2 * MINI_BORDER)
			put_pixel(bx + x, by + y, MINI_BG, game);
	}
}

static void	mini_tiles(t_game *game)
{
	int		i;
	int		j;
	int		cx;
	int		cy;
	t_pos	s;

	cx = (int)(game->player.pos.x / BLOCK);
	cy = (int)(game->player.pos.y / BLOCK);
	j = -MINI_RADIUS - 2;
	while (++j <= MINI_RADIUS + 1)
	{
		i = -MINI_RADIUS - 2;
		while (++i <= MINI_RADIUS + 1)
		{
			s = tile_screen(game, cx + i, cy + j);
			fill_tile(game, (int)s.x, (int)s.y,
				mini_tile_color(game, cy + j, cx + i));
		}
	}
}

static void	mini_player(t_game *game)
{
	int		cx;
	int		cy;
	int		k;
	float	c;
	float	s;

	cx = WIDTH - MINI_MARGIN - MINI_SPAN * MINI_TILE / 2;
	cy = MINI_MARGIN + MINI_SPAN * MINI_TILE / 2;
	fill_tile(game, cx - MINI_TILE / 2, cy - MINI_TILE / 2, MINI_PLAYER);
	c = cos(game->player.angle);
	s = sin(game->player.angle);
	k = -1;
	while (++k < MINI_TILE * 3)
		put_pixel(cx + (int)(c * k), cy + (int)(s * k), MINI_DIR, game);
}

void	draw_minimap(t_game *game)
{
	mini_bg(game);
	mini_tiles(game);
	mini_player(game);
}
