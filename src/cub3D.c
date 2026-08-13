/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:44:14 by wini              #+#    #+#             */
/*   Updated: 2026/08/13 10:42:19 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

static int	valid_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		error_msg("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		error_msg("Error\nMap file must have a .cub extension\n");
		return (1);
	}
	return (0);
}

int	start_game(t_game *game, char *map_file)
{
	init_player(&game->player);
	init_map(&game->map);
	if (parse_file(game, map_file))
		return (1);
	if (!game->map.map)
		return (error_msg("Error\nUnable to load map\n"));
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
	{
		cleanup_game(game);
		return (error_msg("Error\nFailed to get image buffer\n"));
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	printf("\ntest\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (valid_args(argc, argv))
		return (1);
	if (start_game(&game, argv[1]))
		return (1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
