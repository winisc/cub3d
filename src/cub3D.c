/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:44:14 by wini              #+#    #+#             */
/*   Updated: 2026/06/21 22:20:12 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1280, 720, GAME_NAME);
	game->img = mlx_new_image(game->mlx, 1280, 720);
}

static int	valid_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2), 0);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		return (ft_putstr_fd("Error\nMap file must have a .cub extension\n", 2),
			0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!valid_args(argc, argv))
		return (1);
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}
