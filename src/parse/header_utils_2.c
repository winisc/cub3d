/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 20:30:00 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/14 20:30:00 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_texture_id(char *line, char *id)
{
	int	len;

	len = ft_strlen(id);
	return (ft_strncmp(line, id, len) == 0
		&& has_space_after_id(line, len));
}

int	parse_component(char **line, int *value)
{
	int	result;

	*line = skip_spaces(*line);
	if (**line < '0' || **line > '9')
		return (1);
	result = 0;
	while (**line >= '0' && **line <= '9')
	{
		result = result * 10 + (**line - '0');
		if (result > 255)
			return (1);
		(*line)++;
	}
	*value = result;
	*line = skip_spaces(*line);
	return (0);
}

int	parse_rgb(char *line, int *color)
{
	int	r;
	int	g;
	int	b;

	if (parse_component(&line, &r))
		return (1);
	if (*line != ',')
		return (1);
	line++;
	if (parse_component(&line, &g))
		return (1);
	if (*line != ',')
		return (1);
	line++;
	if (parse_component(&line, &b))
		return (1);
	if (*line != '\0')
		return (1);
	*color = (r << 16) | (g << 8) | (b);
	return (0);
}

int	store_texture(char **dest, char *line, int id_len)
{
	char	*path;

	if (*dest)
		return (error_msg("Error\nDuplicate texture\n"));
	path = skip_spaces(line + id_len);
	if (*path == '\0')
		return (error_msg("Error\nMissing texture\n"));
	*dest = ft_strdup(path);
	if (!*dest)
		return (error_msg("Error\nMalloc failed\n"));
	return (0);
}
