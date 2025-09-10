/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:01:43 by tlair             #+#    #+#             */
/*   Updated: 2025/09/10 11:02:02 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	wrap_with_spaces(int *h, int *w, char **res, char **map)
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
