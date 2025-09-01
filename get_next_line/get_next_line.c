/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:25:32 by tlair             #+#    #+#             */
/*   Updated: 2025/05/23 16:30:57 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search_endline(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i + 1);
	return (-1);
}

char	*initialize_stash(char *stash)
{
	if (!stash)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	return (stash);
}

char	*read_and_update_stash(int fd, char *stash)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp;
		if (search_endline(stash) >= 0)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0 || (bytes_read == 0 && (!stash || stash[0] == '\0')))
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*extract_line_and_update_stash(char **stash)
{
	char	*line;
	char	*temp;
	int		endline;

	if (!*stash || (*stash)[0] == '\0')
		return (NULL);
	endline = search_endline(*stash);
	if (endline == -1)
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
	line = ft_strncut(*stash, endline);
	temp = ft_strncut2(*stash, endline, ft_strlen(*stash));
	free(*stash);
	*stash = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = initialize_stash(stash);
	if (!stash)
		return (NULL);
	stash = read_and_update_stash(fd, stash);
	if (!stash)
		return (NULL);
	return (extract_line_and_update_stash(&stash));
}
