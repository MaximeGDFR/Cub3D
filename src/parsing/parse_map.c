/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:44:23 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/12 08:30:12 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	copy_map(t_game *game, char *line)
{
	static t_list	*lines = NULL;
	char			*dup;
	int				len;

	if (line)
	{
		if (is_map_line(game, line))
		{
			dup = ft_strdup(line);
			len = ft_strlen(dup);
			if (len > 0 && dup[len - 1] == '\n')
				dup[len - 1] = '\0';
			ft_lstadd_back(&lines, ft_lstnew(dup));
			return (SUCCESS);
		}
	}
	else
	{
		allocation_map(game, lines);
		finalize_copy(game, lines);
		ft_lstclear(&lines, free);
	}
	return (SUCCESS);
}

int	allocation_map(t_game *game, t_list *lines)
{
	t_list	*tmp;
	int		i;

	tmp = lines;
	game->map.height = ft_lstsize(lines);
	game->map.width = get_max_width(lines);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (error(ERR_MALLOC), FAILURE);
	i = 0;
	while (tmp)
	{
		game->map.grid[i] = malloc(sizeof(char) * (game->map.width + 1));
		if (!game->map.grid[i])
			return (error(ERR_MALLOC), FAILURE);
		game->map.grid[i][game->map.width] = '\0';
		tmp = tmp->next;
		i++;
	}
	game->map.grid[i] = NULL;
	return (SUCCESS);
}

int	finalize_copy(t_game *game, t_list *lines)
{
	int		i;
	int		j;
	char	*line_content;
	t_list	*tmp;

	i = 0;
	tmp = lines;
	while (i < game->map.height)
	{
		j = 0;
		line_content = (char *)tmp->content;
		while (j < game->map.width)
		{
			if (line_content[j])
				game->map.grid[i][j] = line_content[j];
			else
				game->map.grid[i][j] = ' ';
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	game->map.grid[i] = NULL;
	return (SUCCESS);
}

int	get_max_width(t_list *lines)
{
	int		len;
	int		max_width;
	t_list	*tmp;

	tmp = lines;
	max_width = 0;
	while (tmp)
	{
		len = ft_strlen((char *)tmp->content);
		if (len > max_width)
			max_width = len;
		tmp = tmp->next;
	}
	return (max_width);
}
