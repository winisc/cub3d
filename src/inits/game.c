/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 19:00:00 by wini              #+#    #+#             */
/*   Updated: 2026/08/14 19:00:00 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_game_data(t_game *game)
{
	init_player(&game->player);
	init_map(&game->map);
	init_texture_path(&game->texpath);
	init_texture(&game->tex);
	init_colors(&game->colors);
}

int	init_mlx(t_game *game)
{
	init_img(&game->img);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg("Error\nFailed to initialize MLX\n"));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, GAME_NAME);
	if (!game->win)
	{
		cleanup_game(game);
		return (error_msg("Error\nFailed to create window\n"));
	}
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img_ptr)
	{
		cleanup_game(game);
		return (error_msg("Error\nFailed to create image\n"));
	}
	game->img.data = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	if (!game->img.data)
		return (cleanup_game(game),
			error_msg("Error\nFailed to get image buffer\n"));
	return (0);
}
