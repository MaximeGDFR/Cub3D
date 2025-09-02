/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:45:51 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/02 14:23:25 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parsing_map(t_game *game, char *filename)
{
	char	*line;
	int		fd;
	// int		x;
	// int		y;

	(void)game;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error(ERR_OPEN));
	// if (verify_map(fd))
	// 	init_map();
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parsing_texture(line))
			printf("Parsing texture OK");
		free(line);
	}
	return (0);
}

// int	verify_map(int fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		parsing_texture(line);
// 		free(line);
// 	}
// }

int	parsing_texture(char *line)
{
	if (!ft_strncmp(line, "NO", 2)
		||!ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2)
		|| !ft_strncmp(line, "EA", 2))
		return (error(ERR_TEX_SYN));
	return (0);
	
}

// int	parsing_colors(char *line)
// {
// 	int	i;

// 	i = 0;
// 	if (line[i] != 'F' || line[i] != 'C')
// 		return (error(ERR_COL_SYN));
	
// }
