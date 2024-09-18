/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:40:30 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/18 15:01:11 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	free_list(t_list *list)
{
	t_list	*temp_list;

	if (!list)
		return ;
	while (list)
	{
		temp_list = list->next;
		free(list->content);
		free(list);
		list = NULL;
		list = temp_list;
	}
	return ;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	free_all(t_data *data)
{
	HIST_ENTRY	*entry;
	int			i;

	i = 0;
	entry = remove_history(i);
	while (entry)
	{
		free((char *)(entry->line));
		free(entry->data);
		free(entry);
		i++;
		entry = remove_history(i);
	}
	free_array(data->env);
	return (1);
}
