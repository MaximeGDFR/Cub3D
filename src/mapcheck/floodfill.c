/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:39:40 by tlair             #+#    #+#             */
/*   Updated: 2025/09/12 08:29:06 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_pos	define_player_pos(int i, int j, char **map, t_pos pos)
{
	pos.x = j;
	pos.y = i;
	if (map[i][j] == 'N')
		pos.yaw = 90;
	else if (map[i][j] == 'S')
		pos.yaw = 270;
	else if (map[i][j] == 'E')
		pos.yaw = 0;
	else if (map[i][j] == 'W')
		pos.yaw = 180;
	else
		pos.yaw = -1;
	return (pos);
}

static t_pos	find_player_position(char **map)
{
	t_pos	pos;
	int		i;
	int		j;
	int		map_y;

	pos.x = 0;
	pos.y = 0;
	map_y = 0;
	while (map[map_y])
		map_y++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				return (define_player_pos(i, j, map, pos));
			j++;
		}
		i++;
	}
	return (pos);
}

int	flood_fill_recursive(char **map, int x, int y)
{
	if (flood_fill_outside(map, (t_pos){x + 1, y, 0}))
		return (1);
	if (flood_fill_outside(map, (t_pos){x - 1, y, 0}))
		return (1);
	if (flood_fill_outside(map, (t_pos){x, y + 1, 0}))
		return (1);
	if (flood_fill_outside(map, (t_pos){x, y - 1, 0}))
		return (1);
	return (0);
}

int	flood_fill_outside(char **map, t_pos pos)
{
	int		x;
	int		y;
	size_t	len;

	x = (int)pos.x;
	y = (int)pos.y;
	if (y < 0 || !map[y] || x < 0)
		return (0);
	len = ft_strlen(map[y]);
	if ((size_t)x >= len)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (0);
	if (map[y][x] == ' ')
		map[y][x] = 'F';
	else if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W')
		return (1);
	else
		return (0);
	map[y][x] = 'F';
	if (flood_fill_recursive(map, x, y))
		return (1);
	return (0);
}

int	is_playable(char **map, t_player *player)
{
	char	**map_copy;
	char	**map_ext;
	int		res;

	player->pos = find_player_position(map);
	if (player->pos.x == -1 || player->pos.y == -1)
		return (error(ERR_MISSING_PLAYER));
	map_copy = ft_arrdup(map);
	if (!map_copy)
		return (error(ERR_MALLOC));
	map_ext = extend_map(map_copy);
	ft_free_split(map_copy);
	if (!map_ext)
		return (error(ERR_MALLOC));
	res = flood_fill_outside(map_ext, (t_pos){0, 0, 0});
	ft_free_split(map_ext);
	if (res)
		return (error(ERR_MAP_NOT_CLOSED));
	return (0);
}


// TEMP TEST MAIN
void	debug_print(t_player *player, int result)
{
	printf("\n======= INFOS JOUEUR =======\n");
	printf("Position X: %.0f\n", player->pos.x);
	printf("Position Y: %.0f\n", player->pos.y);
	printf("Yaw       : %.0f°\n", player->pos.yaw);

	printf("\n===== RESULTAT FLOODFILL =====\n");
	if (result == 0)
		printf("✅ Map valide et fermée\n");
	else // inatteignable normalement
		printf("❌ Map invalide (code %d)\n", result);
}

// int	main(void)
// {
// 	char	*map[] = {
// 		"       111111111111111111111111  ",
// 		"  1    1000000000110000000000001 ",
// 		" 101   101100000111000      0001 ",
// 		" 101   100100000000000      0001 ",
// 		"110111111011000001110000000000001",
// 		"100000000011000001110111110111111",
// 		"11110111111111011100000010001    ",
// 		"11110111111111011101010010001  1 ",
// 		"11000000110101011100000010001 101",
// 		"10000000000000001100000010001  1 ",
// 		"10000000000000001101010010001    ",
// 		" 1000001110101011111011110N0111  ",
// 		"  11011  1110101 101111010001  1 ",
// 		"    1    1111111 111111111111    ",
// 		NULL
// 	};
// 	t_player	*player;
// 	int			result;

// 	player = malloc(sizeof(t_player));
// 	if (!player)
// 		return (1);
// 	result = is_playable(map, player);
// 	if (result == 1)
// 		return (0);

// 	print_map(map);
// 	debug_print(player, result);

// 	free(player);
// 	return (0);
// }
