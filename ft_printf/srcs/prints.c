/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:33:31 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/01 15:06:13 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(unsigned char c, int *count)
{
	int	i;

	i = write(1, &c, 1);
	if (i == -1)
		*count = -1;
	else
		*(count) += 1;
}

void	ft_putstr(char *str, int *count)
{
	if (!str)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (*str)
	{
		ft_putchar(*str++, count);
		if (*count < 0)
			return ;
	}
}

void	put_nbr(int n, int *count)
{
	if (*count < 0)
		return ;
	if (n < 0)
	{
		ft_putchar('-', count);
		if (*count < 0)
			return ;
		if (n == -2147483648)
		{
			ft_putchar('2', count);
			if (*count < 0)
				return ;
			n = -147483648;
		}
		n = -n;
	}
	if (n / 10)
	{
		put_nbr(n / 10, count);
		if (*count < 0)
			return ;
	}
	ft_putchar(n % 10 + '0', count);
	if (*count < 0)
		return ;
}

void	put_unsigned_int(unsigned int n, int *count)
{
	if (*count < 0)
		return ;
	if (n / 10)
	{
		put_unsigned_int(n / 10, count);
		if (*count < 0)
			return ;
	}
	ft_putchar(n % 10 + '0', count);
	if (*count < 0)
		return ;
}

void	print_hex(unsigned long n, int *count)
{
	if (n / 16)
	{
		print_hex(n / 16, count);
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
		ft_putchar(n % 16 + 'a' - 10, count);
	if (*count < 0)
		return ;
}
