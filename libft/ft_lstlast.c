/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodefro <mgodefro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:28:57 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/19 12:53:34 by mgodefro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	if (lst == NULL)
		return (NULL);
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

/*int	main()
{
	t_list *head = NULL;

	t_list *last_content = ft_lstlast(head);
	if (last_content != NULL)
		printf("Le dernier element est : %s\n", (char *)last_content->content);
	else
	printf("La liste est vide.\n");
	return (0);
}*/
