/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:14:48 by hle-roi           #+#    #+#             */
/*   Updated: 2023/10/19 15:38:58 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = -1;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			tmp = i;
		i++;
	}
	if ((unsigned char)c == '\0')
		return (((char *)s + i));
	if (tmp != -1)
		return (((char *)s + tmp));
	return (NULL);
}
