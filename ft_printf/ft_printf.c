/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:04:24 by flhensel          #+#    #+#             */
/*   Updated: 2025/11/06 14:35:16 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	write_string(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		i++;
		count++;
	}
	return (count);
}

int	search(va_list args, const char format)
{
	int	length;

	length = 0;
	if (format == 'c')
		length += write_char(va_arg(args, int));
	else if (format == 's')
		length += write_string(va_arg(args, char *));
	else if (format == 'p')
		length += write_pointer(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		length += write_number(va_arg(args, int));
	else if (format == 'u')
		length += write_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		length += write_hex(va_arg(args, unsigned int));
	else if (format == 'X')
		length += write_hexx(va_arg(args, unsigned int));
	else if (format == '%')
		length += write_char('%');
	return (length);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		length;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	length = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			length += search(args, str[i + 1]);
			i++;
		}
		else if (str[i] != '%')
			length += write_char(str[i]);
		i++;
	}
	va_end(args);
	return (length);
}
