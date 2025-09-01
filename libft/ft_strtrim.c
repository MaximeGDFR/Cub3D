/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <j@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:31:12 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/22 17:01:14 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	is_in_set(char const c, char const *set)
{
	size_t	current;

	current = 0;
	while (set[current] != '\0')
	{
		if (set[current] == c)
			return (1);
		current++;
	}
	return (0);
}

static char	*empty_string(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, "", 1);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (is_in_set(s1[start], set))
		start++;
	i = ft_strlen(s1);
	end = i - 1;
	if (start == i)
		return (empty_string());
	while (is_in_set(s1[end], set))
		end--;
	trimmed = malloc((end - start + 2) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, (s1 + start), (end - start + 2));
	return (trimmed);
}

/*int main()
{
    char const *s1 = "   Hello World!   ";
    char const *set = " ";
    char *trimmed;

    trimmed = ft_strtrim(s1, set);

    if (trimmed == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return (1);
    }

    printf("Avant trim : '%s'\n", s1);
    printf("Après trim : '%s'\n", trimmed);

    free(trimmed);

    return (0);
}*/