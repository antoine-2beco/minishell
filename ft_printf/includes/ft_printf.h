/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:21:19 by hle-roi           #+#    #+#             */
/*   Updated: 2023/10/20 14:55:41 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(unsigned char c, int *count);
void	ft_putstr(char *str, int *count);
void	put_nbr(int n, int *count);
void	put_unsigned_int(unsigned int n, int *count);
void	print_hex(unsigned long n, int *count);

#endif
