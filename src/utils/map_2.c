/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:59:12 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/12 17:12:06 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid_neighbor(char c)
{
	return (c == '1' || c == ' ');
}

int	get_row_len(t_game *game, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	return (ft_strlen(game->map.map[y]));
}

int	check_border_row(char *row)
{
	int	x;

	x = first_non_space(row);
	while (row[x])
	{
		if (row[x] != '1' && row[x] != ' ')
			return (1);
		x++;
	}
	return (0);
}

int	count_rows(t_game *game)
{
	int	y;

	y = 0;
	while (game->map.map[y])
		y++;
	return (y);
}
