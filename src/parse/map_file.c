/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 17:46:16 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/11 21:48:51 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**read_file(int fd);
int		parse_file(t_game *game, char *map_file);

//int		split_header(char **lines, char ***header_lines)
//{

//}
//int		split_map(char **lines, char ***map_lines)
//{

//}

//int		*split_file(char **lines, char ***header_lines, char ***map_lines);

char	**read_file(int fd)
{
	char	**lines;
	char	**tmp;
	char	*line;
	int		count;
	int		cap;
	
	cap = 20;
	count = 0;
	lines = malloc(sizeof(char *) * cap);
	if (!lines)
		return (NULL);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (count + 1 >= cap)
		{
			cap *= 2;
			tmp = realloc(lines, sizeof(char *) * cap);
			if (!tmp)
				return (free_lines(lines, count), NULL);
			lines = tmp;
		}
		lines[count] = line;
		count++;
	}
	lines[count] = NULL;
	return (lines);
}

int	parse_file(t_game *game, char *map_file)
{
	int		fd;
	char	**lines;
	//char	**header_lines;
	//char	**map_lines;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	lines = read_file(fd);
	close(fd);
	if (!lines)
		return (1);
	//if (split_file(lines, &map_header, &map_lines)) //TODO:
	//	return (free(lines), 1);
	free(lines);
	//if (parse_header())
	//	return (1);
	//game->map.map = map_lines;
	if (check_map_chars(game))
		return (1);
	if (validate_map_shape(game))
		return (1);
	if (find_spawn(game))
		return (1);
	return (0);
}
