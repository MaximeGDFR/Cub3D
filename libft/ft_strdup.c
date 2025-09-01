/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:30:05 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/19 15:07:07 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*dup;

	i = 0;
	size = ft_strlen((char *)s) + 1;
	dup = (char *)malloc(size * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

/*int main()
{
    char s [] = "Hello world !";
    char *result;

    result = ft_strdup(s);
    printf("Src : %s\n", s);
    printf("Copy : %s\n", result);
    free(result);
    return (0);
}*/