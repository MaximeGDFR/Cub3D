/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <j@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:27:35 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/27 11:39:13 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}

/*int main()
{
    char s1 [20] = "Hello world";
    char s2 [] = "Hello world !";
    size_t n = 13;

    printf("Avant memmove: s1 = %s, s2 = %s\n", s1, s2);
    ft_memmove(s1, s2, n);
    printf("Apres memmove: s1 = %s\n", s1);

    return (0);
}*/