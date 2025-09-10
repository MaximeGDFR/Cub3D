/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:07:49 by tlair             #+#    #+#             */
/*   Updated: 2025/09/10 10:59:48 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	line_print(int len, char *str)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%s", str);
		i++;
	}
}

static void	print_map_title(int max_len)
{
	int	i;

	printf("\n");
	if (max_len < 19)
	{
		printf("MAP ORIGINALE\n");
		printf("╔");
		i = 0;
		line_print(max_len, "═");
		printf("╗\n");
	}
	else
	{
		printf("╔");
		line_print((max_len + 2 - 13) / 2, "═");
		printf(" MAP ORIGINALE ");
		line_print((max_len + 2 - 13) / 2, "═");
		printf("╗\n");
	}
}

static void	choose_char(char c)
{
	if (c == '1')
		printf("\033[38;5;250m█\033[0m");
	else if (c == '0')
		printf("\033[48;5;236m \033[0m");
	else if (c == ' ')
		printf(" ");
	else if (c == 'N')
		printf("\033[38;5;196;48;5;236m▲\033[0m");
	else if (c == 'S')
		printf("\033[38;5;196;48;5;236m▼\033[0m");
	else if (c == 'E')
		printf("\033[38;5;196;48;5;236m▶\033[0m");
	else if (c == 'W')
		printf("\033[38;5;196;48;5;236m◀\033[0m");
	else
		printf("?");
}

static void	print_map_objs(int i, int j, int max_len, char **map)
{
	while (map[i])
	{
		printf("║  ");
		j = 0;
		while (map[i][j])
		{
			choose_char(map[i][j]);
			j++;
		}
		while (j < max_len)
		{
			printf(" ");
			j++;
		}
		printf("  ║\n");
		i++;
	}
}

void	print_map(char **map)
{
	int	i;
	int	j;
	int	max_len;
	int	total_width;

	max_len = 0;
	i = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]);
		if (j > max_len)
			max_len = j;
		i++;
	}
	print_map_title(max_len);
	printf("║  ");
	line_print(max_len, " ");
	printf("  ║\n");
	print_map_objs(0, j, max_len, map);
	printf("║  ");
	line_print(max_len, " ");
	printf("  ║\n");
	printf("╚");
	line_print(max_len + 4, "═");
	printf("╝\n");
}
