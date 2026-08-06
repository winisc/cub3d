/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:35:07 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/06 19:12:48 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3D.h"

char	**read_file_lines(int fd)
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

int	pad_map(t_game *game)
{
	int		y;
	int		width;
	char	*padded;

	width = map_width(game); //TODO:
	y = 0;
	while (game->map.map[y])
	{
		padded = ft_calloc(width + 1, sizeof(char));
		if (!padded)
			return (1);
		ft_memset(padded, ' ', width);
		ft_strlcpy(padded, game->map.map[y], ft_strlen(game->map.map[y]));
		free(game->map.map[y]);
		game->map.map[y] = padded;
		y++;
	}
	game->colors.width = width;
	game->colors.height = map_height(game); //TODO:
	return (0);
}

//int	parse_header(int fd, t_texpath *texpath, t_colors *colors)
//{
//	char	*line;

//	line = get_next_line(fd);
//	if (fd < 0)
//		return (1);
//}

//int	parse_map_lines(fd)
//{
//	return (read_file_lines(fd));
//}

int	parse_map_file(t_game *game, char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	//if (parse_header(fd, &game->texpath, &game->colors)) //TODO:
	//	return (1);
	game->map.map = parse_map_lines(fd); //TODO:
	close(fd);
	if (!game->map.map)
		return (1);
	// if (validate_map(game))
	// 	return (1);
	if (find_spawn(game))
		return (1);
	// if (is_enclosed(game)) //TODO:
	// 	return (1);
	return (0);
}
