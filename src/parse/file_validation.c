/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 17:46:16 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/15 00:58:56 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	**grow_lines(char **lines, int *cap, int count)
{
	char	**tmp;

	if (count + 1 < *cap)
		return (lines);
	*cap *= 2;
	tmp = realloc(lines, sizeof(char *) * *cap);
	if (!tmp)
		return (free_lines(lines, count), NULL);
	return (tmp);
}

char	**read_file(int fd)
{
	char	**lines;
	char	*line;
	int		count;
	int		cap;

	cap = READ_CAP;
	count = 0;
	lines = malloc(sizeof(char *) * cap);
	if (!lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		lines = grow_lines(lines, &cap, count);
		if (!lines)
			return (free(line), NULL);
		strip_newline(line);
		lines[count++] = line;
		line = get_next_line(fd);
	}
	lines[count] = NULL;
	return (lines);
}

int	split_header_and_map(char **lines, char ***header, char ***map)
{
	int	map_start;
	int	total;
	int	header_count;
	int	map_count;

	total = 0;
	map_start = find_map_start(lines);
	if (map_start < 0)
		return (error_msg("Error\nCouldn't find map\n"));
	if (check_map_end(lines, map_start))
		return (1);
	while (lines[total])
		total++;
	header_count = count_range(lines, 0, map_start);
	map_count = count_range(lines, map_start, total);
	if (alloc_split(header, map, header_count, map_count))
		return (1);
	copy_range(*header, lines, 0, map_start);
	copy_range(*map, lines, map_start, total);
	return (0);
}

static int	validate_parsed(t_game *game)
{
	if (check_map_chars(game))
		return (1);
	if (find_spawn(game))
		return (1);
	if (validate_map_flood(game))
		return (1);
	return (0);
}

int	parse_file(t_game *game, char *map_file)
{
	int		fd;
	char	**lines;
	char	**header;
	char	**map;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (error_msg("Error\nCannot open file\n"));
	lines = read_file(fd);
	close(fd);
	if (!lines)
		return (error_msg("Error\nUnable to read file\n"));
	if (split_header_and_map(lines, &header, &map))
		return (free_str_array(lines), 1);
	free(lines);
	game->map.map = map;
	if (parse_header(header, &game->texpath, &game->colors))
		return (free_str_array(header), 1);
	free_str_array(header);
	return (validate_parsed(game));
}
