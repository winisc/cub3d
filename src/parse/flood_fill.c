/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 00:00:00 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 00:00:00 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	push(t_stack *st, int y, int x)
{
	int	*new;

	if (st->size >= st->cap)
	{
		st->cap *= 2;
		new = realloc(st->data, sizeof(int) * st->cap * 2);
		if (!new)
			return (1);
		st->data = new;
	}
	st->data[st->size * 2] = y;
	st->data[st->size * 2 + 1] = x;
	st->size++;
	return (0);
}

static int	push_neighbors(t_stack *st, int y, int x)
{
	if (push(st, y - 1, x) || push(st, y + 1, x)
		|| push(st, y, x + 1) || push(st, y, x - 1))
		return (1);
	return (0);
}

int	flood_fill(t_game *game, char **visited, int y0, int x0)
{
	t_stack	st;
	int		y;
	int		x;
	char	tile;

	st.cap = 1024;
	st.size = 0;
	st.data = malloc(sizeof(int) * st.cap * 2);
	if (!st.data || push(&st, y0, x0))
		return (free(st.data), 1);
	while (st.size > 0)
	{
		st.size--;
		y = st.data[st.size * 2];
		x = st.data[st.size * 2 + 1];
		tile = get_tile(game, y, x);
		if (tile == ' ' || tile == '\0')
			return (free(st.data), 1);
		if (tile == '1' || is_visited(visited, y, x))
			continue ;
		visited[y][x] = 'V';
		if (push_neighbors(&st, y, x))
			return (free(st.data), 1);
	}
	return (free(st.data), 0);
}
