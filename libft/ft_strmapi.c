/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <j@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:30:47 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/27 11:02:08 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	if (s == NULL || f == NULL)
		return (NULL);
	result = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*int main()
{
    char str [] = "Hello world !";
    char *new_str = ft_strmapi(str, my_function);

    if (new_str != NULL)
    {
        printf("%s\n", str);
        printf("%s\n", new_str);
        free(new_str);
    }
    return (0);
}*/