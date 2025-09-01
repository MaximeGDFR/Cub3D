/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:00:01 by tlair             #+#    #+#             */
/*   Updated: 2024/12/10 10:37:00 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	char	*joined;
	int		i;
	int		j;

	i = 0;
	j = 0;
	joined = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buffer) + 1));
	if (!joined)
		return (NULL);
	while (stash[i])
	{
		joined[i] = stash[i];
		i++;
	}
	while (buffer[j])
	{
		joined[i + j] = buffer[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

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
