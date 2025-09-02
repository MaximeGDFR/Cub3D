/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:45:51 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/02 17:23:59 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_map(t_map *map, int fd)
{
	char	*line = NULL;
	char	*next_line = NULL;
	int		width;

	map->height = 0;
	map->width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			next_line = get_next_line(fd);
			if (next_line)
			{
				if (!check_line_is_map(next_line))
				{
					free(next_line);
					continue ;
				}
				else
					return (error(ERR_INVALID_MAP));
			}
		}
		else
		{
			if (check_line_is_map(line))
			{
				width = ft_strlen(line);
				if (width > map->width)
					map->width = width;
				map->height++;
			}
			free(line);
		}
	}
	allocate_map(map);
	return (0);
}

int	allocate_map(t_map *map)
{
	int	y = 0;

	map->grid = (char **)malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return (error(ERR_MALLOC));
	while (y < map->height)
	{
		map->grid[y] = (char *)malloc(sizeof(char) * map->width + 1);
		if (!map->grid[y])
		{
			while (--y >= 0)
				free(map->grid[y]);
			free(map->grid);
			return (error(ERR_MALLOC));
		}
		y++;
	}
	return (0);
}

int	fill_map(t_game *game, char *filename)
{
	int		x;
	int		y;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error(ERR_OPEN));
	init_map(&game->map, fd);
	x = 0;
	while (1)
	{
		line = get_next_line(fd);
		printf("Readed line : %s\n", line);
		if (!check_line_is_map(line))
		{
			free(line);
			continue ;
		}
		else
		{
			y = 0;
			while (line[y])
			{
				game->map.grid[x][y] = line[y];
				y++;
			}
			game->map.grid[x][y] = '\n';
			x++;
		}
		free(line);
	}
	return (0);
}

int	check_line_is_map(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (!is_space(line[i]) || !is_valid_char(line[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (-1);
	return (0);
}
