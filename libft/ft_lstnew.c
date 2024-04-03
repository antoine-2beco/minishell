/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:09:41 by hle-roi           #+#    #+#             */
/*   Updated: 2023/12/11 10:33:20 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(long int content)
{
	t_list	*new;

	if (INT_MIN <= content && content <= INT_MAX)
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		new->content = content;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}
