/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:40:12 by tclaereb          #+#    #+#             */
/*   Updated: 2023/10/30 13:04:04 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ln;

	if (n < 0)
	{
		ln = (unsigned int)n * -1;
		ft_putchar_fd('-', fd);
	}
	else
		ln = (unsigned int)n;
	if (ln / 10 >= 1)
	{
		ft_putnbr_fd(ln / 10, fd);
		ft_putnbr_fd(ln % 10, fd);
	}
	else
		ft_putchar_fd(ln + 48, fd);
}
