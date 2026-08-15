/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 19:23:36 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/14 23:22:25 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parse_texture_line(char *line, t_texpath *texpath)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (is_texture_id(line, "NO"))
		return (store_texture(&texpath->no, line, 2));
	if (is_texture_id(line, "SO"))
		return (store_texture(&texpath->so, line, 2));
	if (is_texture_id(line, "WE"))
		return (store_texture(&texpath->we, line, 2));
	if (is_texture_id(line, "EA"))
		return (store_texture(&texpath->ea, line, 2));
	return (1);
}

static int	parse_color_line(char *line, t_colors *colors)
{
	char	*value;

	value = skip_spaces(line + 1);
	if (line[0] == 'F')
	{
		if (colors->floor_color_set == 1)
			return (error_msg("Error\nDuplicate floor color\n"));
		if (parse_rgb(value, &colors->floor_color))
			return (error_msg("Error\nInvalid floor color\n"));
		colors->floor_color_set = 1;
	}
	else
	{
		if (colors->ceiling_color_set == 1)
			return (error_msg("Error\nDuplicate ceiling color\n"));
		if (parse_rgb(value, &colors->ceiling_color))
			return (error_msg("Error\nInvalid ceiling color\n"));
		colors->ceiling_color_set = 1;
	}
	return (0);
}

static int	parse_header_line(char *line, t_texpath *texpath, t_colors *colors)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (is_texture_id(trimmed, "NO") || is_texture_id(trimmed, "SO")
		|| is_texture_id(trimmed, "EA") || is_texture_id(trimmed, "WE"))
		return (parse_texture_line(trimmed, texpath));
	if (is_color(trimmed, 'F') || is_color(trimmed, 'C'))
		return (parse_color_line(trimmed, colors));
	if (trimmed[0] == '\0')
		return (0);
	return (error_msg("Error\nUnknown header identifier\n"));
}

int	check_required_header(t_texpath *texpath, t_colors *colors)
{
	if (!texpath->no || !texpath->we || !texpath->ea || !texpath->so)
		return (error_msg("Error\nMissing texture path\n"));
	if (colors->floor_color_set == 0)
		return (error_msg("Error\nMissing floor texture\n"));
	if (colors->ceiling_color_set == 0)
		return (error_msg("Error\nMissing ceiling texture\n"));
	return (0);
}

int	parse_header(char **lines, t_texpath *texpath, t_colors *colors)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] != '\0')
		{
			printf("Parsing header line: [%s]\n", lines[i]);
			if (parse_header_line(lines[i], texpath, colors))
				return (1);
		}
		i++;
	}
	if (check_required_header(texpath, colors))
		return (1);
	return (0);
}
