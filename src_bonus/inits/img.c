/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:32:32 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 19:00:13 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_img(t_img *img)
{
	img->img_ptr = NULL;
	img->addr = NULL;
	img->data = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->height = 0;
	img->line_len = 0;
	img->width = 0;
}

void	init_texture(t_tex *texture)
{
	init_img(&texture->ea);
	init_img(&texture->no);
	init_img(&texture->so);
	init_img(&texture->we);
}

void	init_texture_path(t_texpath *texpath)
{
	texpath->ea = NULL;
	texpath->no = NULL;
	texpath->so = NULL;
	texpath->we = NULL;
}

void	init_colors(t_colors *colors)
{
	colors->ceiling_color = 0;
	colors->floor_color = 0;
	colors->ceiling_color_set = 0;
	colors->floor_color_set = 0;
}
