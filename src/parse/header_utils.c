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
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	has_space_after_id(char *line, int len)
{
	return (line[len] == ' ' || line[len] == '\t');
}
