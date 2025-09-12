/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:44:45 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/12 08:30:16 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	fill_texture_info(t_game *game, char *line, int *i)
{
	if (line[*i] == 'N' && line[*i + 1] == 'O' && !(game->tex->north))
		game->tex->north = get_path_texture(line, i);
	else if (line[*i] == 'S' && line[*i + 1] == 'O' && !(game->tex->south))
		game->tex->south = get_path_texture(line, i);
	else if (line[*i] == 'W' && line[*i + 1] == 'E' && !(game->tex->west))
		game->tex->west = get_path_texture(line, i);
	else if (line[*i] == 'E' && line[*i + 1] == 'A' && !(game->tex->east))
		game->tex->east = get_path_texture(line, i);
	else
		return (FAILURE);
	return (SUCCESS);
}

char	*get_path_texture(char *line, int *i)
{
	int		len;
	char	*path;

	len = 0;
	path = NULL;
	*i += 2;
	while (line[*i] && isspace((unsigned char)line[*i]))
		(*i)++;
	if (!line[*i])
		return (NULL);
	path = ft_strdup(&line[*i]);
	if (!path)
		return (error(ERR_MALLOC), NULL);
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	return (path);
}
