/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:25:57 by hle-roi           #+#    #+#             */
/*   Updated: 2023/10/20 15:40:27 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex_min(unsigned int n, int *count)
{
	if (*count < 0)
		return ;
	if (n / 16)
	{
		print_hex_min(n / 16, count);
		if (*count < 0)
			return ;
	}
	if (n % 16 < 10)
	{
		ft_putchar(n % 16 + '0', count);
		if (*count < 0)
			return ;
	}
	else
	{
		ft_putchar(n % 16 + 'a' - 10, count);
		if (*count < 0)
			return ;
	}
}

void	print_hex_maj(unsigned int n, int *count)
{
	if (*count < 0)
		return ;
	if (n / 16)
	{
		print_hex_maj(n / 16, count);
		if (*count < 0)
			return ;
	}
	if (n % 16 < 10)
	{
		ft_putchar(n % 16 + '0', count);
		if (*count < 0)
			return ;
	}
	else
	{
		ft_putchar(n % 16 + 'A' - 10, count);
		if (*count < 0)
			return ;
	}
}

void	get_conversion(char c, va_list args, int *count)
{
	if (c == 'd' || c == 'i')
		put_nbr(va_arg(args, int), count);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (c == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (c == 'u')
		put_unsigned_int(va_arg(args, unsigned int), count);
	else if (c == 'p')
	{
		ft_putstr("0x", count);
		if (*count < 0)
			return ;
		print_hex(va_arg(args, unsigned long), count);
	}
	else if (c == 'x')
		print_hex_min(va_arg(args, unsigned int), count);
	else if (c == 'X')
		print_hex_maj(va_arg(args, unsigned int), count);
	else
		ft_putchar(c, count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1])
			{
				get_conversion(str[i + 1], args, &count);
				i += 2;
			}
		}
		else
			ft_putchar(str[i++], &count);
		if (count < 0)
			return (count);
	}
	va_end(args);
	return (count);
}
