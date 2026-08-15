/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:44:14 by wini              #+#    #+#             */
/*   Updated: 2026/08/14 23:33:11 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	error_msg(char *msg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(RESET, 2);
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
	init_game_data(game);
	if (parse_file(game, map_file))
	{
		cleanup_game(game);
		return (1);
	}
	if (!game->map.map)
		return (error_msg("Error\nUnable to load map\n"));
	if (init_mlx(game))
		return (1);
	if (load_textures(game))
	{
		cleanup_game(game);
		return (1);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
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
