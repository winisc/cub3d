/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 12:09:05 by wini              #+#    #+#             */
/*   Updated: 2026/06/22 12:11:41 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_point pos1, t_point pos2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;

	delta_x = pos2.x - pos1.x;
	delta_y = pos2.y - pos1.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	return (distance(delta_x, delta_y) * cos(angle));
}
