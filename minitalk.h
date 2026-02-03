/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:25:11 by florianh          #+#    #+#             */
/*   Updated: 2026/02/03 14:11:31 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/types.h>
# include "libft/libft.h"

int	ft_printf(const char *format, ...);

typedef struct s_client
{
	int	bit_confirmed;
	int	message_confirmed;
}	t_client;

#endif