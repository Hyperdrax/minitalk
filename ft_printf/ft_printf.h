/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:04:27 by flhensel          #+#    #+#             */
/*   Updated: 2025/11/06 14:32:07 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);
int		search(va_list args, const char format);
int		write_char(char c);
int		write_string(char *str);
int		write_number(int n);
int		write_unsigned(unsigned int n);
int		pointer_length(uintptr_t num);
int		write_pointer(unsigned long long ptr);
void	pointer_help(uintptr_t num);
int		write_hex(unsigned int n);
int		write_hexx(unsigned int n);
void	write_hex_helper(unsigned int n);
void	write_hexx_helper(unsigned int n);
int		hex_length(unsigned int n);
char	*ft_utoa(unsigned int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);

#endif