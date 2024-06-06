/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:43:12 by tclaereb          #+#    #+#             */
/*   Updated: 2024/04/01 09:44:12 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdio.h>
char	*concat(uintptr_t n)
{
	char	*adress;
	char	*s;

	if (!n)
		return (ft_strdup("0x0"));
	adress = ft_putaddress_base16(n);
	if (!adress)
		return (NULL);
	s = ft_strjoin("0x", adress);
	free(adress);
	if (!s)
		return (NULL);
	return (s);
}

int	arg_p(va_list args)
{
	uintptr_t	n;
	int			len;
	char		*s;
	char		*start;

	n = va_arg(args, uintptr_t);
	len = 0;
	s = concat(n);
	if (!s)
		return (-1);
	start = s;
	while (*s)
	{
		if (ft_putchar_fd(*s, 1) == -1)
		{
			free(start);
			return (-1);
		}
		s++;
		len++;
	}
	free(start);
	return (len);
}
