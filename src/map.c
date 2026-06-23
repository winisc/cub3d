/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 00:19:06 by wini              #+#    #+#             */
/*   Updated: 2026/06/22 19:03:57 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// substituir por leitura/parse real depois
char	**get_map(char *map_file)
{
	char	**map;

	(void)map_file;
	map = malloc(sizeof(char *) * 12);
	if (!map)
		return (NULL);
	map[0] = "1111111111111";
	map[1] = "1000000000001";
	map[2] = "1000001100001";
	map[3] = "1000000000001";
	map[4] = "1000000000001";
	map[5] = "1010000000001";
	map[6] = "1010000000001";
	map[7] = "1011000000001";
	map[8] = "1001000000001";
	map[9] = "1000000000001";
	map[10] = "1111111111111";
	map[11] = NULL;
	return (map);
}

void	draw_map(t_game *game)
{
	char	**map;
	t_point	pos;
	int		x;
	int		y;

	map = game->map;
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
