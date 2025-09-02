/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:39:40 by tlair             #+#    #+#             */
/*   Updated: 2025/09/02 17:11:55 by mgodefro         ###   ########.fr       */
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

static int	is_traversable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	flood_fill(char **map, t_pos pos)
{
	int		x;
	int		y;
	size_t	len;

	if (!map)
		return (error(ERR_INVALID_MAP));
	x = (int)pos.x;
	y = (int)pos.y;
	if (y < 0 || x < 0)
		return (error(ERR_OUT_OF_BOUNDS));
	if (!map[y])
		return (error(ERR_MISSING_LINE));
	len = ft_strlen(map[y]);
	if ((size_t)x >= len)
		return (error(ERR_OUT_OF_LINE));
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == ' ')
		return (error(ERR_SPACE_MISPLACED));
	if (map[y][x] == 'F')
		return (0);
	if (!is_traversable(map[y][x]))
		return (error(ERR_INVALID_CHAR));
	map[y][x] = 'F';
	pos.x = x + 1; pos.y = y;
	if (flood_fill(map, pos))
		return (error(ERR_FLOOD_FAIL));
	pos.x = x - 1; pos.y = y;
	if (flood_fill(map, pos))
		return (error(ERR_FLOOD_FAIL));
	pos.x = x; pos.y = y + 1;
	if (flood_fill(map, pos))
		return (error(ERR_FLOOD_FAIL));
	pos.x = x; pos.y = y - 1;
	if (flood_fill(map, pos))
		return (error(ERR_FLOOD_FAIL));
	return (0);
}

int	is_playable(char **map, t_player player)
{
	char	**map_copy;
	int		res;

	player.pos = find_player_position(map);
	if (player.pos.x == -1 || player.pos.y == -1)
		return (error(ERR_MISSING_PLAYER), 1);
	map_copy = ft_arrdup(map);
	if (!map_copy)
		return (error(ERR_MALLOC), 1);
	res = flood_fill(map_copy, player.pos);
	ft_free_split(map_copy);
	if (res)
		return (error(ERR_MAP_NOT_CLOSED));
	return (0);
}

// TEMP TEST MAIN
// int	main(void)
// {
// 	char	*map[] = {
// 		"1111111111111111111",
// 		"1001001001001001001",
// 		"1001001001001001001",
// 		"1001001001001001001",
// 		"1001001000001001001",
// 		"100000000S000000001",
// 		"1000011111111000001",
// 		"1111000000000001111",
// 		"1000000101010000001",
// 		"1111111111111111111",
// 		NULL
// 	};
// 	t_player	player;
// 	int			result;

// 	ft_bzero(&player, sizeof(t_player));
// 	result = is_playable(map, player);
// 	if (result == 0)
// 		printf("✅ Map is valid and closed !\n");
// 	else
// 		printf("❌ Map is invalid (error code %d)\n", result);
// 	return (0);
// }
