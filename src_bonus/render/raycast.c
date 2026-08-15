/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:20:00 by wini              #+#    #+#             */
/*   Updated: 2026/08/15 19:00:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;
	int	row_len;

	if (!game || !game->map.map || px < 0 || py < 0)
		return (1);
	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (!game->map.map[y])
		return (1);
	row_len = ft_strlen(game->map.map[y]);
	if (x < 0 || x >= row_len)
		return (1);
	if (game->map.map[y][x] == '1')
		return (1);
	return (0);
}

float	wall_height(float dist)
{
	if (dist <= 0.0001f)
		return (HEIGHT);
	return ((BLOCK / dist) * (WIDTH / 2));
}
