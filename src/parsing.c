/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:50:49 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/02 16:36:37 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_file_format(char *filename)
{
	int	i;

	i = ft_strlen(filename);
	if (i < 4 || filename[i - 1] != 'b' || filename[i - 2] != 'u'
		|| filename[i - 3] != 'c' || filename[i - 4] != '.')
		error(ERR_FORMAT);
	return (0);
}

int	parsing(int ac, char **av)
{
	if (ac > 2)
		error(ERR_UTIL);
	else
	{
		if (!check_file_format(av[2]))
			return (-1);
	}
	return (0);
}

// int	parsing_texture(char *line)
// {
// 	int	i;

// 	if (ft_strncmp(line, "NO", 2)
// 		|| ft_strncmp(line, "SO", 2)
// 		|| ft_strncmp(line, "WE", 2)
// 		|| ft_strncmp(line, "EA", 2))

// 	return (0);
// }

// int	parsing_colors(char *line)
// {
// 	int	i;

// 	i = 0;
// 	if (line[i] != 'F' || line[i] != 'C')
// 		return (error(ERR_COL_SYN));
	
// }
