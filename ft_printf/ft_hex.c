/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:23:07 by flhensel          #+#    #+#             */
/*   Updated: 2025/11/06 14:25:23 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_hex(unsigned int n)
{
	int	length;

	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	else
	{
		write_hex_helper(n);
		length = hex_length(n);
	}
	return (length);
}

int	write_hexx(unsigned int n)
{
	int	length;

	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	else
	{
		write_hexx_helper(n);
		length = hex_length(n);
	}
	return (length);
}

void	write_hex_helper(unsigned int n)
{
	if (n >= 16)
	{
		write_hex_helper(n / 16);
		write_hex_helper(n % 16);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', 1);
		else
			ft_putchar_fd(n - 10 + 'a', 1);
	}
}

void	write_hexx_helper(unsigned int n)
{
	if (n >= 16)
	{
		write_hexx_helper(n / 16);
		write_hexx_helper(n % 16);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', 1);
		else
			ft_putchar_fd(n - 10 + 'A', 1);
	}
}

int	hex_length(unsigned int n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		length++;
		n = n / 16;
	}
	return (length);
}
