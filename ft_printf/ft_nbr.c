/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:20:39 by flhensel          #+#    #+#             */
/*   Updated: 2025/11/06 14:20:46 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_number(int n)
{
	int		length;
	char	*nbr;

	length = 0;
	nbr = ft_itoa(n);
	length = write_string(nbr);
	free(nbr);
	return (length);
}

char	*ft_utoa(unsigned int n)
{
	char			*str;
	unsigned int	num;
	int				len;

	num = n;
	len = 1;
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

int	write_unsigned(unsigned int n)
{
	int		length;
	char	*nbr;

	length = 0;
	nbr = ft_utoa(n);
	length = write_string(nbr);
	free(nbr);
	return (length);
}
