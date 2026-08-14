/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 17:45:24 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/14 18:00:07 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_header_line(const char *line)
{
	return (
		ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0
		|| line[0] == ' '
		|| line[0] == '\n'
		|| line[0] == '\0'
	);
}

int	is_color(char *line, char id)
{
	return (line[0] == id && (line[1] == ' ' || line[1] == '\t'));
}

int	is_blank(const char *line)
{
	return (line[0] == '\0');
}

char	*skip_spaces(char *line)
{
	while (*line == ' '  || *line == '\t')
		line++;
	return (line);
}

int	has_space_after_id(char *line, int len)
{
	return (line[len] == ' ' || line[len] == '\t');
}

int	texture_id(char *line, char *id)
{
	int	len;

	len = ft_strlen(id);
	return (ft_strncmp(line, id, len) == 0
		&& has_space_after_id(line, len));
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
