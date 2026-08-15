/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:37:13 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 19:00:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	load_one_texture(t_game *game, t_img *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
		return (error_msg("Error\nFailed to load texture\n"));
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->data)
		return (error_msg("Error\nFailed to read texture data\n"));
	return (0);
}

int	load_textures(t_game *game)
{
	if (load_one_texture(game, &game->tex.no, game->texpath.no))
		return (1);
	if (load_one_texture(game, &game->tex.so, game->texpath.so))
		return (1);
	if (load_one_texture(game, &game->tex.we, game->texpath.we))
		return (1);
	if (load_one_texture(game, &game->tex.ea, game->texpath.ea))
		return (1);
	return (0);
}

int	tex_pixel(t_img *tex, int x, int y)
{
	int	index;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	index = y * tex->line_len + x * (tex->bpp / 8);
	return (*(int *)(tex->data + index));
}

t_img	*pick_texture(t_game *game, t_ray *ray, float cos_a, float sin_a)
{
	if (ray->side == 0)
	{
		if (cos_a > 0)
			return (&game->tex.we);
		return (&game->tex.ea);
	}
	if (sin_a > 0)
		return (&game->tex.no);
	return (&game->tex.so);
}
