/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:50:49 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/01 17:22:48 by mgodefro         ###   ########.fr       */
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

int	error(char *msg)
{
	ft_putstr_fd("./cub3d Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
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

