/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:20:00 by wini              #+#    #+#             */
/*   Updated: 2026/06/22 19:09:26 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_point pos, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(pos.x + i, pos.y, color, game);
		put_pixel(pos.x, pos.y + i, color, game);
		put_pixel(pos.x + size, pos.y + i, color, game);
		put_pixel(pos.x + i, pos.y + size, color, game);
		i++;
	}
}

void	draw_wall(t_game *game, int column, float height)
{
	int	start_y;
	int	end;

	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		put_pixel(column, start_y, 0x0000FF, game);
		start_y++;
	}
}

void	clear_image(t_game *game)
{
	ft_bzero(game->data, game->size_line * HEIGHT);
}
