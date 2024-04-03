/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:17:48 by hle-roi           #+#    #+#             */
/*   Updated: 2023/10/17 16:23:11 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				rep;

	i = 0;
	rep = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		rep = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (rep == 0)
			i++;
		else
			return (rep);
	}
	return (rep);
}
