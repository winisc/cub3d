/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:44:14 by wini              #+#    #+#             */
/*   Updated: 2026/08/03 18:12:53 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	valid_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nMap file must have a .cub extension\n", 2);
		return (0);
	}
	return (1);
}

void	start_game(t_game *game, char *map_file)
{
	init_player(&game->player);
	init_img(&game->img);
	game->map.map = get_map(map_file);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, GAME_NAME);
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!valid_args(argc, argv))
		return (1);
	start_game(&game, argv[1]);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
