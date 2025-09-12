/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:44:39 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/12 08:30:07 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	fill_color_ceilling(t_game *game, char *line, int *i)
{
	int	index_rgb;
	int	value;
	int	digits_count;

	index_rgb = 0;
	(*i)++;
	while (line[*i] && index_rgb <= 2)
	{
		if (isdigit((unsigned char)line[*i]))
		{
			value = 0;
			digits_count = 0;
			value = extract_value(line, value, i, digits_count);
			if (fill_rgb(&game->ceilling, &index_rgb, value))
				return (FAILURE);
		}
		else if (line[*i] == ',' || isspace((unsigned char)line[*i]))
			(*i)++;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

int	extract_value(char *line, int value, int *i, int digits_count)
{
	while (line[*i] && ft_isdigit((unsigned char)line[*i]))
	{
		value = value * 10 + (line[*i] - '0');
		(*i)++;
		digits_count++;
		if (digits_count > 3)
			return (-1);
	}
	if (value < 0 || value > 255)
		return (error(ERR_COL_VAL), FAILURE);
	return (value);
}

int	fill_rgb(t_color *color_to_fill, int *index_rgb, int value)
{
	if (*index_rgb == 0)
		color_to_fill->r = value;
	else if (*index_rgb == 1)
		color_to_fill->g = value;
	else if (*index_rgb == 2)
		color_to_fill->b = value;
	else
		return (FAILURE);
	(*index_rgb)++;
	if (*index_rgb > 2)
		return (FAILURE);
	return (SUCCESS);
}

int	fill_color_floor(t_game *game, char *line, int *i)
{
	int	index_rgb;
	int	value;
	int	digits_count;

	index_rgb = 0;
	(*i)++;
	while (line[*i] && index_rgb <= 2)
	{
		if (isdigit((unsigned char)line[*i]))
		{
			value = 0;
			digits_count = 0;
			value = extract_value(line, value, i, digits_count);
			if (fill_rgb(&game->floor, &index_rgb, value))
				return (FAILURE);
		}
		else if (line[*i] == ',' || isspace((unsigned char)line[*i]))
			(*i)++;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}
