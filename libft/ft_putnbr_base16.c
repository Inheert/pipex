/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base16.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:06:49 by tclaereb          #+#    #+#             */
/*   Updated: 2024/03/25 13:45:33 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countsize(long long n)
{
	int	count;

	if (n == 0)
		return (2);
	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

static void	recursive(char *ptr, unsigned int n, unsigned int size, int *i)
{
	char				*base;

	base = "0123456789abcdef";
	if (n / 16 >= 1)
	{
		recursive(ptr, n / 16, size, i);
		recursive(ptr, n % 16, size, i);
	}
	else
	{
		ptr[*i] = base[n];
		(*i)++;
	}
}

char	*ft_putnbr_base16(unsigned int n)
{
	char				*ptr;
	unsigned int		size;
	int					i;

	size = countsize(n);
	i = 0;
	ptr = ft_calloc(size, sizeof(char));
	if (!ptr)
		return (NULL);
	recursive(ptr, n, size, &i);
	return (ptr);
}
