/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:29:36 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/19 12:29:37 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	else
	{
		while (s[i] != '\0')
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
	write (fd, "\n", 1);
}

/*int main()
{
    int fd = 1;
    char *message = "Hello, world!";
    
    ft_putendl_fd(message, fd);

    return (0);
}*/
