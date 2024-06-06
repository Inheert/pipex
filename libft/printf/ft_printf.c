/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:43:12 by tclaereb          #+#    #+#             */
/*   Updated: 2024/03/25 13:41:39 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	manage_symbols(const char *format, va_list args)
{
	format++;
	if (*format == 'c')
		return (arg_c(args));
	else if (*format == 's')
		return (arg_s(args));
	else if (*format == 'd' || *format == 'i')
		return (arg_d(args));
	else if (*format == 'u')
		return (arg_u(args));
	else if (*format == 'x')
		return (arg_x(args, 0));
	else if (*format == 'X')
		return (arg_x(args, 1));
	else if (*format == 'p')
		return (arg_p(args));
	else if (*format == '%')
		return (arg_percent());
	return (-1);
}

int	display_and_count(const char *format, va_list args)
{
	int	len;
	int	symbol_len;

	len = 0;
	while (*format)
	{
		if (*format != '%')
		{
			if (ft_putchar_fd(*format, 1) == -1)
				return (-1);
			len++;
			format++;
		}
		else
		{
			symbol_len = manage_symbols(format, args);
			if (symbol_len == -1)
				return (-1);
			else
				len += symbol_len;
			format += 2;
		}
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	len = display_and_count(format, args);
	va_end(args);
	return (len);
}
