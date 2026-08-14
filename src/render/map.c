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

void	draw_map(t_game *game)
{
	char	**map;
	t_pos	pos;
	int		x;
	int		y;

	map = game->map.map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				pos.x = x * BLOCK;
				pos.y = y * BLOCK;
				draw_square(pos, BLOCK, 0x0000FF, game);
			}
			x++;
		}
		y++;
	}
}
