/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtakiyos <mtakiyos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:35:07 by mtakiyos          #+#    #+#             */
/*   Updated: 2026/08/07 16:46:17 by mtakiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3D.h"

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

int	pad_map(t_game *game)
{
	int		y;
	int		width;
	char	*padded;

	width = map_width(game);
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
	game->colors.height = map_height(game);
	return (0);
}

char	**parse_header(int fd, t_texpath *texpath, t_colors *colors)
{
	(void)texpath;
	(void)colors;
	return (read_file(fd));
}

char	**parse_map(int fd)
{
	int		i;
	char	**line;
	
	i = 0;
	line = read_file(fd);
	while (is_header_line(line))
		i++;
	return ();
}

int	parse_file(t_game *game, char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	//if (parse_header(fd, &game->texpath, &game->colors)) //TODO:
	//	return (1);
	game->map.map = parse_map(fd);
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
