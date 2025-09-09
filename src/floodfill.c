/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:39:40 by tlair             #+#    #+#             */
/*   Updated: 2025/09/09 17:41:20 by tlair            ###   ########.fr       */
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

static t_pos	define_player_pos(int i, int j, char **map, t_pos pos)
{
	pos.x = j;
	pos.y = i;
	pos.yaw = player_orientation(map[i][j]);
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

static int	is_traversable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	flood_fill_outside(char **map, t_pos pos);

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
	else if (is_traversable(map[y][x]))
		return (1);
	else
		return (0);
	map[y][x] = 'F';
	if (flood_fill_recursive(map, x, y))
		return (1);
	return (0);
}

void	wrap_with_spaces(int *h, int *w, char **res, char **map)
{
	int	i;

	i = 0;
	while (i < *h)
	{
		res[i + 1] = ft_calloc(*w + 3, sizeof(char));
		ft_memset(res[i + 1], ' ', *w + 2);
		ft_memcpy(res[i + 1] + 1, map[i], ft_strlen(map[i]));
		res[i + 1][*w + 2] = '\0';
		i++;
	}
}

static char	**norm_is_bad_idk_how_to_name_this(char **res, int h, int w)
{
	res[h + 1][w + 2] = '\0';
	res[h + 2] = NULL;
	return (res);
}

char	**extend_map(char **map)
{
	int		h;
	int		w;
	int		len;
	char	**res;

	h = 0;
	w = 0;
	while (map[h])
	{
		len = (int)ft_strlen(map[h]);
		if (len > w)
			w = len;
		h++;
	}
	res = malloc(sizeof(char *) * (h + 3));
	if (!res)
		return (NULL);
	res[0] = ft_calloc(w + 3, sizeof(char));
	ft_memset(res[0], ' ', w + 2);
	res[0][w + 2] = '\0';
	wrap_with_spaces(&h, &w, res, map);
	res[h + 1] = ft_calloc(w + 3, sizeof(char));
	ft_memset(res[h + 1], ' ', w + 2);
	return (norm_is_bad_idk_how_to_name_this(res, h, w));
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
/* petite fonction pour afficher joliment la map */
static void	print_map(char **map)
{
	int	i, j, max_len;

	printf("======= MAP ORIGINALE =======\n\n");
	
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

int	main(void)
{
	char	*map[] = {
		"       111111111111111111111111 ",
		"  1    1000000000110000000000001 ",
		" 101   101100000111000      0001 ",
		" 101   100100000000000      0001 ",
		"110111111011000001110000000000001",
		"100000000011000001110111110111111",
		"11110111111111011100000010001    ",
		"11110111111111011101010010001  1 ",
		"11000000110101011100000010001 101",
		"10000000000000001100000010001  1 ",
		"10000000000000001101010010001   ",
		" 1000001110101011111011110N0111  ",
		"  110111 1110101 101111010001  1 ",
		"   11111 1111111 111111111111    ",
		NULL
	};
	t_player	*player;
	int			result;

	player = malloc(sizeof(t_player));
	if (!player)
		return (1);
	result = is_playable(map, player);
	if (result == 1)
		return (0);

	print_map(map);
	debug_print(player, result);

	free(player);
	return (0);
}
