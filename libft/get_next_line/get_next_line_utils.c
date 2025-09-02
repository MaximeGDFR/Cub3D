/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:00:01 by tlair             #+#    #+#             */
/*   Updated: 2025/09/02 13:58:21 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strncut(char *s, int n)
{
	char	*cut;
	int		i;

	i = 0;
	cut = malloc(sizeof(char) * (n + 1));
	if (!cut)
		return (NULL);
	while (i < n)
	{
		cut[i] = s[i];
		i++;
	}
	cut[i] = '\0';
	return (cut);
}

char	*ft_strncut2(char *s, int start, int end)
{
	char	*cut;
	int		i;

	if (!s || start >= end)
		return (NULL);
	cut = malloc(sizeof(char) * (end - start + 1));
	if (!cut)
		return (NULL);
	i = 0;
	while (start < end && s[start])
	{
		cut[i] = s[start];
		i++;
		start++;
	}
	cut[i] = '\0';
	return (cut);
}
