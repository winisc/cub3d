/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 21:42:10 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/14 13:10:10 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
}

int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] != '\0' && !is_header_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	count_range(char **lines, int start, int delimiter)
{
	int	count;

	count = 0;
	while (lines[start] && start < delimiter)
	{
		start++;
		count++;
	}
	return (count);
}

int	alloc_split(char ***header, char ***map, int header_count, int map_count)
{
	*header = malloc(sizeof(char *) * (header_count + 1));
	*map = malloc(sizeof(char *) * (map_count + 1));
	if (!*header || !*map)
	{
		free(*header);
		free(*map);
		*header = NULL;
		*map = NULL;
		return (1);
	}
	return (0);
}

void	copy_range(char **dest, char **src, int start, int delimiter)
{
	int	i;

	i = 0;
	while (start < delimiter)
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = NULL;
}
