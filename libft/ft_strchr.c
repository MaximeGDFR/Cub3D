/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <j@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:30:01 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/30 16:11:55 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)(s + i));
	return (0);
}

/*int main() {
    const char *str = "Hello, world!";
    char ch = 'o';
    
    char *result = strchr(str, ch);
    
    if (result != NULL)
    {
        printf("'%c' a ete trouve a la position : %ld\n", ch, result - str);
    }
    else
    {
        printf("Le caractere '%c' n'a pas ete trouve.\n", ch);
    }
    
    return (0);
}*/