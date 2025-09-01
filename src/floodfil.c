/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:39:40 by tlair             #+#    #+#             */
/*   Updated: 2025/09/01 17:20:58 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static double	player_orientation(char c)
{
	if (c == 'N')
		return (90);
	if (c == 'S')
		return (270);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (180);
	return (-1);
}

static t_pos	find_player_position(char **map)
{
	t_pos	pos;
	int		i;
	int		j;

	pos.x = -1;
	pos.y = -1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				pos.x = j;
				pos.y = i;
				pos.yaw = player_orientation(map[i][j]);
				return (pos);
			}
			j++;
		}
		i++;
	}
	return (pos);
}

int	flood_fill(char **map, t_pos pos)
{
	if (pos.x < 0 || pos.y < 0 || !map[(int)pos.y] || !map[(int)pos.y][(int)pos.x]
		|| map[(int)pos.y][(int)pos.x] == '1')
		return (0);
	map[(int)pos.y][(int)pos.x] = '1';
	pos.x++;
	flood_fill(map, pos);
	pos.x -= 2;
	flood_fill(map, pos);
	pos.x++;
	pos.y++;
	flood_fill(map, pos);
	pos.y -= 2;
	flood_fill(map, pos);
	return (1);
}

int	is_playable(char **map, t_player player)
{
	char	**map_copy;

	player.pos = find_player_position(map);
	if (player.pos.x == -1 || player.pos.y == -1)
		return (error(ERR_MISSING_PLAYER));
	map_copy = ft_arrdup(map);
	if (!map_copy)
		return (error(ERR_MALLOC));
	flood_fill(map_copy, player.pos);
	ft_free_split(map_copy);
	return (0);
}
