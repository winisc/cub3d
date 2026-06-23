/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:25:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/22 19:10:52 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_minimap_view(t_game *game, t_player *player)
{
	draw_square(player->pos, 10, 0xFFF000, game);
	draw_map(game);
}

void	cast_rays(t_player *player, t_game *game)
{
	int		i;
	float	fov;
	float	angle_step;
	float	ray_angle;
	float	dist;

	fov = PI / 3;
	angle_step = fov / WIDTH;
	ray_angle = player->angle - fov / 2;
	i = 0;
	while (i < WIDTH)
	{
		dist = ray_distance(player, game, ray_angle);
		if (!player->debug)
			draw_wall(game, i, wall_height(dist));
		ray_angle += angle_step;
		i++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player_controller(player);
	clear_image(game);
	if (player->debug)
		render_minimap_view(game, player);
	cast_rays(player, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
