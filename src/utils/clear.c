/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 17:41:28 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/03 17:35:29 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_textures(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->tex.no.img_ptr)
		mlx_destroy_image(game->mlx, game->tex.no.img_ptr);
	if (game->tex.so.img_ptr)
		mlx_destroy_image(game->mlx, game->tex.so.img_ptr);
	if (game->tex.we.img_ptr)
		mlx_destroy_image(game->mlx, game->tex.we.img_ptr);
	if (game->tex.ea.img_ptr)
		mlx_destroy_image(game->mlx, game->tex.ea.img_ptr);
}

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_texpath(t_texpath *tex)
{
	free(tex->no);
	free(tex->so);
	free(tex->we);
	free(tex->ea);
	tex->no = NULL;
	tex->so = NULL;
	tex->we = NULL;
	tex->ea = NULL;
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	destroy_textures(game);
	if (game->img.img_ptr && game->mlx)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_str_array(game->map.map);
	game->map.map = NULL;
	free_texpath(&game->texpath);
}
