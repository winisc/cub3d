/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:20:00 by wini              #+#    #+#             */
/*   Updated: 2026/08/15 19:00:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (!game || !game->img.data || game->img.line_len <= 0)
		return ;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->img.line_len + x * game->img.bpp / 8;
	game->img.data[index] = color & 0xFF;
	game->img.data[index + 1] = (color >> 8) & 0xFF;
	game->img.data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_wall(t_game *game, int column, t_img *tex, t_ray ray)
{
	int	height;
	int	start;
	int	y;
	int	tex_x;
	int	tex_y;

	height = (int)wall_height(ray.dist);
	start = (HEIGHT - height) / 2;
	tex_x = (int)(ray.wall_x / BLOCK * tex->width);
	y = start;
	while (y < start + height)
	{
		tex_y = (int)((float)(y - start) / height * tex->height);
		if (y >= 0 && y < HEIGHT)
			put_pixel(column, y, tex_pixel(tex, tex_x, tex_y), game);
		y++;
	}
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(x, y, game->colors.ceiling_color, game);
			else
				put_pixel(x, y, game->colors.floor_color, game);
			x++;
		}
		y++;
	}
}

void	clear_image(t_game *game)
{
	if (!game || !game->img.data || game->img.line_len <= 0)
		return ;
	ft_bzero(game->img.data, game->img.line_len * HEIGHT);
}
