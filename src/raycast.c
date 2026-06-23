/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:20:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/22 12:15:22 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (1);
	return (0);
}

t_point	cast_ray(t_game *game, t_point start, float ray_angle)
{
	t_point	ray;
	float	cos_angle;
	float	sin_angle;

	ray = start;
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!touch(ray.x, ray.y, game))
	{
		if (game->player.debug)
			put_pixel(ray.x, ray.y, 0xFF0000, game);
		ray.x += cos_angle;
		ray.y += sin_angle;
	}
	return (ray);
}

float	wall_height(float dist)
{
	return ((BLOCK / dist) * (WIDTH / 2));
}

float	ray_distance(t_player *player, t_game *game, float ray_angle)
{
	t_point	center;
	t_point	hit;

	center.x = player->pos.x + 5;
	center.y = player->pos.y + 5;
	hit = cast_ray(game, center, ray_angle);
	return (fixed_dist(center, hit, game));
}
