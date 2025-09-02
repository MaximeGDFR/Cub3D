/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:39:40 by tlair             #+#    #+#             */
/*   Updated: 2025/09/02 18:10:19 by tlair            ###   ########.fr       */
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
	int		map_height;

	pos.x = -1;
	pos.y = -1;
	map_height = 0;
	while (map[map_height])
		map_height++;
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
				pos.y = map_height - 1 - i;
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
	int		x = (int)pos.x;
	int		y = (int)pos.y;
	size_t	len;

	if (y < 0 || x < 0 || !map[y])
		return (1);
	len = ft_strlen(map[y]);
	if ((size_t)x >= len)
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (0);
	if (map[y][x] == ' ')
		return (1);
	if (!is_traversable(map[y][x]))
		return (1);
	map[y][x] = 'F';
	if (flood_fill(map, (t_pos){x + 1, y, 0}))
		return (1);
	if (flood_fill(map, (t_pos){x - 1, y, 0}))
		return (1);
	if (flood_fill(map, (t_pos){x, y + 1, 0}))
		return (1);
	if (flood_fill(map, (t_pos){x, y - 1, 0}))
		return (1);
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
/* petite fonction pour afficher joliment la map */
static void	print_map(char **map)
{
	int	i, j, max_len;

	// Calculer la longueur maximale d'une ligne
	max_len = 0;
	i = 0;
	while (map[i])
	{
		int len = ft_strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}

	// Largeur totale = map + 2*2 marges
	int total_width = max_len + 4;

	// Afficher le haut du rectangle avec 1 espace de marge
	printf("╔");
	for (j = 0; j < total_width; j++)
		printf("═");
	printf("╗\n");

	// Ligne de marge supérieure
	printf("║  ");
	for (j = 0; j < max_len; j++)
		printf(" ");
	printf("  ║\n");

	// Afficher la map avec les bords verticaux et 2 espaces de marge
	i = 0;
	while (map[i])
	{
		printf("║  ");
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				printf("\033[38;5;250m█\033[0m"); // mur
			else if (map[i][j] == '0')
				printf("\033[48;5;236m \033[0m"); // sol
			else if (map[i][j] == ' ')
				printf(" "); // espace vide
			else if (map[i][j] == 'N')
				printf("\033[38;5;196;48;5;236m▲\033[0m"); // joueur
			else if (map[i][j] == 'S')
				printf("\033[38;5;196;48;5;236m▼\033[0m"); // joueur
			else if (map[i][j] == 'E')
				printf("\033[38;5;196;48;5;236m▶\033[0m"); // joueur
			else if (map[i][j] == 'W')
				printf("\033[38;5;196;48;5;236m◀\033[0m"); // joueur
			else
				printf("?"); // caractère inattendu
			j++;
		}
		// Remplir les espaces manquants si la ligne est plus courte
		while (j < max_len)
		{
			printf(" ");
			j++;
		}
		printf("  ║\n");
		i++;
	}

	// Ligne de marge inférieure
	printf("║  ");
	for (j = 0; j < max_len; j++)
		printf(" ");
	printf("  ║\n");

	// Afficher le bas du rectangle
	printf("╚");
	for (j = 0; j < total_width; j++)
		printf("═");
	printf("╝\n");
}

int	main(void)
{
	// char	*map[] = {
	// 	"1111111111111111111",
	// 	"1001001001001001001",
	// 	"1001001001001001001",
	// 	"1001001001001001001",
	// 	"1001001000001001001",
	// 	"100000000000S000001",
	// 	"1000011111111000001",
	// 	"1111000000000001111",
	// 	"1000000101010000001",
	// 	"1111111111111111111",
	// 	NULL
	// };
	char	*map[] = {
		"       1111111111111111111111111",
		"       1000000000110000000000001",
		"       1011000001110000000000001",
		"       1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111110111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL
	};
	t_player	player = {0};
	int			result;

	printf("=== MAP ORIGINALE ===\n\n");
	print_map(map);

	result = is_playable(map, player);

	printf("\n=== INFOS JOUEUR ===\n");
	printf("Position X: %d\n", (int)player.pos.x);
	printf("Position Y: %d\n", (int)player.pos.y);
	printf("Yaw       : %.2f°\n", player.pos.yaw);

	printf("\n=== RESULTAT FLOODFILL ===\n");
	if (result == 0)
		printf("✅ Map valide et fermée\n");
	else
		printf("❌ Map invalide (code %d)\n", result);
	return (0);
}
