/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:54:47 by hle-roi           #+#    #+#             */
/*   Updated: 2023/10/19 13:06:14 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void	*))
{
	t_list	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	tmp = lst;
	del(tmp->content);
	free(tmp);
	lst = NULL;
}
