/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 20:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/08/15 19:00:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	init_dda(t_dda *d, t_pos start, float angle)
{
	d->pos.x = start.x / BLOCK;
	d->pos.y = start.y / BLOCK;
	d->dir.x = cos(angle);
	d->dir.y = sin(angle);
	d->map_x = (int)d->pos.x;
	d->map_y = (int)d->pos.y;
	d->delta.x = fabsf(1.0f / d->dir.x);
	d->delta.y = fabsf(1.0f / d->dir.y);
}

static void	init_sides(t_dda *d)
{
	if (d->dir.x < 0)
	{
		d->step_x = -1;
		d->side_dist.x = (d->pos.x - d->map_x) * d->delta.x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist.x = (d->map_x + 1 - d->pos.x) * d->delta.x;
	}
	if (d->dir.y < 0)
	{
		d->step_y = -1;
		d->side_dist.y = (d->pos.y - d->map_y) * d->delta.y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist.y = (d->map_y + 1 - d->pos.y) * d->delta.y;
	}
}

static void	run_dda(t_dda *d, t_game *game)
{
	while (1)
	{
		if (d->side_dist.x < d->side_dist.y)
		{
			d->side_dist.x += d->delta.x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_dist.y += d->delta.y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (touch(d->map_x * BLOCK, d->map_y * BLOCK, game))
			break ;
	}
}

t_ray	cast_ray(t_game *game, t_pos start, float ray_angle)
{
	t_dda	d;
	t_ray	ray;
	float	perp;
	float	wall;

	init_dda(&d, start, ray_angle);
	init_sides(&d);
	run_dda(&d, game);
	if (d.side == 0)
		perp = d.side_dist.x - d.delta.x;
	else
		perp = d.side_dist.y - d.delta.y;
	if (d.side == 0)
		wall = d.pos.y + perp * d.dir.y;
	else
		wall = d.pos.x + perp * d.dir.x;
	ray.side = d.side;
	ray.wall_x = (wall - floorf(wall)) * BLOCK;
	ray.dist = perp * BLOCK;
	ray.hit.x = start.x + d.dir.x * perp * BLOCK;
	ray.hit.y = start.y + d.dir.y * perp * BLOCK;
	return (ray);
}
