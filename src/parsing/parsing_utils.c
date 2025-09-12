/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:48:32 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/12 08:52:00 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (SUCCESS); // Inverted -> SUCCESS = FAILURE
		i++;
	}
	return (FAILURE);
}

int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W'
		|| c == ' ')
		return (SUCCESS);
	return (FAILURE);
}

int	is_map_line(t_game *game, char *line)
{
	int	i;

	if (!line)
		return (error(ERR_INVALID_MAP), FAILURE);
	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '1' || line[i] == '0')
			i++;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			if (!game->map.has_player)
			{
				game->map.has_player = 1;
				i++;
			}
			else
				return (error("More than one player."), FAILURE);
		}
		else
			return (FAILURE);
	}
	return (SUCCESS);
}
