/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:26:51 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/19 13:32:41 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	i = 0;
	current = lst;
	if (lst == NULL)
		return (0);
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/*int	main()
{
	t_list *head = NULL;

	int	size = ft_lstsize(head);
	printf("La taille de la liste est : %s\n", size);
	return (0);
}*/
