/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:45:51 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/01 17:56:38 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	parsing_map(t_game *game, char *filename)
{
	char	*line;
	int		fd;
	int		x;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error(ERR_OPEN));
	while (line = get_next_line(fd))
	{
		if (!parsing_texture())
			return (error(ERR_TEXTURE));
		if (!parsing_colors)
			return (error(ERR_COLORS));
		if (!parsing_map())
			return (error(ERR_MAP));
		free(line);
	}
}

int	parsing_texture(char *line)
{

}

int	parsing_colors(char *line)
{

}

int	parsing_map(char *line)
{
	
}
