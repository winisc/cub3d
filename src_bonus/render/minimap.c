/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 19:00:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	mini_bg(t_game *game)
{
	int	x;
	int	y;
	int	left;
	int	span;

	left = mini_left() - MINI_BORDER;
	span = mini_size() + 2 * MINI_BORDER;
	y = 0;
	while (y < span)
	{
		x = 0;
		while (x < span)
		{
			put_pixel(left + x, MINI_MARGIN - MINI_BORDER + y, MINI_BG, game);
			x++;
		}
		y++;
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
	j = -MINI_RADIUS - 1;
	while (j <= MINI_RADIUS + 1)
	{
		i = -MINI_RADIUS - 1;
		while (i <= MINI_RADIUS + 1)
		{
			s = tile_screen(game, cx + i, cy + j);
			fill_tile(game, (int)s.x, (int)s.y,
				mini_tile_color(game, cy + j, cx + i));
			i++;
		}
		j++;
	}
}

static void	mini_player(t_game *game)
{
	int		cx;
	int		cy;
	int		k;
	float	dx;
	float	dy;

	cx = mini_left() + mini_size() / 2;
	cy = MINI_MARGIN + mini_size() / 2;
	fill_tile(game, cx - MINI_TILE / 2, cy - MINI_TILE / 2, MINI_PLAYER);
	dx = cos(game->player.angle);
	dy = sin(game->player.angle);
	k = 0;
	while (k < MINI_TILE * 3)
	{
		put_pixel(cx + (int)(dx * k), cy + (int)(dy * k), MINI_DIR, game);
		k++;
	}
}

void	draw_minimap(t_game *game)
{
	mini_bg(game);
	mini_tiles(game);
	mini_player(game);
}
