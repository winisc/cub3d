/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:59:12 by wini              #+#    #+#             */
/*   Updated: 2026/07/28 18:04:37 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start_game(t_game *game, char *map_file)
{
	//if (!game || !map_file)
	//	return (0);
	init_player(&game->player);
	init_img(&game->img);
	
	game->map = get_map(map_file);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, GAME_NAME);
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.line_len,
			&game->img.endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}
