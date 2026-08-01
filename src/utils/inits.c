/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:32:32 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/07/31 21:34:51 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_img(t_img *img)
{
	img->addr = NULL;
	img->data = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->height = 0;
	img->line_len = 0;
	img->width = 0;
}

void	init_player(t_player *player)
{
	player->pos.x = WIDTH / 2;
	player->pos.y = HEIGHT / 2;
	player->angle = PI / 2;
	player->key_up = 0;
	player->key_down = 0;
	player->key_strafe_left = 0;
	player->key_strafe_right = 0;
	player->key_left_rotate = 0;
	player->key_right_rotate = 0;
	player->debug = DEBUG;
}
