/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 12:09:05 by wini              #+#    #+#             */
/*   Updated: 2026/08/03 17:55:27 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_spawn pos1, t_spawn pos2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;

	delta_x = pos2.x - pos1.x;
	delta_y = pos2.y - pos1.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	return (distance(delta_x, delta_y) * cos(angle));
}

double	get_time_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

double	compute_delta_time(t_game *game)
{
	double	current_time;
	double	delta_time;

	current_time = get_time_seconds();
	delta_time = current_time - game->last_frame_time;
	game->last_frame_time = current_time;
	return (delta_time);
}
