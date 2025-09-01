/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: j <j@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:28:27 by mgodefro          #+#    #+#             */
/*   Updated: 2024/10/22 15:32:21 by j                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	ft_swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	get_num_length(long n)
{
	int	len;

	len = 1;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*handle_zero_case(void)
{
	char	*result;

	result = (char *)malloc(2 * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	num;
	int		num_len;
	int		is_neg;

	num = n;
	if (num == 0)
		return (handle_zero_case());
	is_neg = (num < 0);
	if (is_neg)
		num = -num;
	num_len = get_num_length(num);
	result = (char *)malloc(num_len + is_neg + 1);
	if (result == NULL)
		return (NULL);
	if (is_neg)
		result[0] = '-';
	result[num_len + is_neg] = '\0';
	while (num > 0)
	{
		result[--num_len + is_neg] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}

/*int main()
{
    char *str;

    str = ft_itoa(1234);
    printf("1234 : %s\n", str);
    free(str);

    str = ft_itoa(-42);
    printf("-42 : %s\n", str);
    free(str);

    str = ft_itoa(2123456789);
    printf("2123456789 : %s\n", str);
    free(str);

    return (0);
}*/
