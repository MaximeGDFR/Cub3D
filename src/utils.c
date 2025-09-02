/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:14:32 by tlair             #+#    #+#             */
/*   Updated: 2025/09/02 14:19:26 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	error(char *msg)
{
	ft_putstr_fd("./cub3d Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

char	**ft_arrdup(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		if (!new[i])
		{
			while (i-- > 0)
				free(new[i]);
			free(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
