/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximegdfr <maximegdfr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:50:38 by mgodefro          #+#    #+#             */
/*   Updated: 2025/09/12 08:29:30 by maximegdfr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


static void	init_program(t_game *game)
{
	game->tex->north = NULL;
	game->tex->south = NULL;
	game->tex->east = NULL;
	game->tex->west = NULL;
	game->ceilling.r = 0;
	game->ceilling.g = 0;
	game->ceilling.b = 0;
	game->floor.r = 0;
	game->floor.g = 0;
	game->floor.b = 0;
}

int	main(int ac, char **av)
{
	t_game	game;
	int		i;

	(void)ac;
	init_program(&game);
	init_map(&game.map);
	parsing_data(&game, av[1]);
	printf("DATA PARSED :\n");
	printf("TEXTURES\n");
	printf("North : %s\nSouth : %s\nEast : %s\nWest : %s\n",
		game.tex->north, game.tex->south, game.tex->east, game.tex->west);
	printf("COLORS\n");
	printf("Ceilling : %d, %d, %d\nFloor : %d, %d, %d\n",
		game.ceilling.r, game.ceilling.g, game.ceilling.b, game.floor.r,
		game.floor.g, game.floor.b);
	printf("MAP (%d x %d) :\n", game.map.height, game.map.width);
	i = 0;
	while (i < game.map.height)
	{
		printf("%s\n", game.map.grid[i]);
		i++;
	}
	return (0);
}

