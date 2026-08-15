/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:25:00 by wini              #+#    #+#             */
/*   Updated: 2026/08/15 19:07:50 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_rays(t_player *player, t_game *game)
{
	int		i;
	float	ray_angle;
	t_ray	ray;
	t_pos	center;
	t_img	*tex;

	center.x = player->pos.x + 5;
	center.y = player->pos.y + 5;
	ray_angle = player->angle - (PI / 3) / 2;
	i = 0;
	while (i < WIDTH)
	{
		ray = cast_ray(game, center, ray_angle, player->angle);
		tex = pick_texture(game, &ray, cos(ray_angle), sin(ray_angle));
		draw_wall(game, i, tex, ray);
		ray_angle += (PI / 3) / WIDTH;
		i++;
	}
}

int	draw_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	player_controller(game);
	clear_image(game);
	draw_background(game);
	cast_rays(&game->player, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}
