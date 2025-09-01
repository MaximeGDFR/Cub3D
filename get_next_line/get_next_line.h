/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlair <tlair@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:59:10 by tlair             #+#    #+#             */
/*   Updated: 2024/12/10 10:31:19 by tlair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>

int		ft_strlen(const char *s);
char	*ft_strjoin(char *stash, char *buffer);
char	*ft_strncut(char *s, int n);
char	*ft_strncut2(char *s, int start, int end);
char	*get_next_line(int fd);

#endif