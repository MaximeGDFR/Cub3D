/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <j@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:31:08 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/27 11:29:42 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*occ;

	i = 0;
	occ = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			occ = (char *)(s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		occ = (char *)(s + i);
	return (occ);
}

/*int main()
{
    const char *str = "teste";
    char ch = '\0';
    char *result = ft_strrchr(str, ch);
    
    if (result != NULL)
        printf("Last '%c' est a la position : %ld\n", ch, result - str);
    else
        printf("Le caractere '%c' n'a pas ete trouve.\n", ch);
    return (0);
}*/