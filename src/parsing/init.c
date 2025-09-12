/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:53:48 by maximegdfr        #+#    #+#             */
/*   Updated: 2025/09/12 08:30:01 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	init_map(t_map *map)
{
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	return (SUCCESS);
}

int	parsing_data(t_game *game, char *filename)
{
	int	fd;

	fd = 0;
	if (!check_file_format(filename))
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (error(ERR_OPEN), FAILURE);
	}
	get_file_info(game, fd);
	return (SUCCESS);
}

int	get_file_info(t_game *game, int fd)
{
	char	*line;
	t_state	state;

	state = BEFORE_MAP;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (game->ceilling.b && game->floor.b && game->tex->north
			&& game->tex->south && game->tex->east && game->tex->west)
			state = IN_MAP;
		if (parsing_line(game, &state, line) != 0)
			return (FAILURE);
		free(line);
	}
	copy_map(game, NULL);
	return (SUCCESS);
}

int	parsing_line(t_game *game, t_state *state, char *line)
{
	if (*state == BEFORE_MAP && line_is_empty(line))
		return (SUCCESS);
	if (*state == BEFORE_MAP && !line_is_empty(line))
	{
		if (select_parser(game, state, line))
			return (FAILURE);
	}
	if (*state == IN_MAP)
	{
		if (!is_map_line(game, line))
		{
			*state = AFTER_MAP;
			return (SUCCESS);
		}
		else
		{
			copy_map(game, line);
			return (SUCCESS);
		}
	}
	if (*state == AFTER_MAP && (!line_is_empty(line)))
		return (FAILURE);
	return (SUCCESS);
}

int	select_parser(t_game *game, t_state *state, char *line)
{
	int	i;

	i = 0;
	(void)state;
	while (isspace(line[i]))
		i++;
	if (line[i] == 'C')
		fill_color_ceilling(game, line, &i);
	else if (line[i] == 'F')
		fill_color_floor(game, line, &i);
	else if (line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'W' || line[i] == 'E')
		fill_texture_info(game, line, &i);
	else if (is_map_line(game, line))
	{
		*state = IN_MAP;
		copy_map(game, line);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
