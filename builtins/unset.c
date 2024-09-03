/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:26 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/03 13:14:49 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static int	removevar(t_list *before, t_list **node, char *arg)
{
	if (!ft_strncmp((*node)->content, ft_strjoin(arg, "="), \
				ft_strlen(arg)))
	{
		if (!node)
			return (0);
		if (!before)
		{
			before = (*node)->next;
			free((*node)->content);
			free(*node);
			*node = before;
		}
		before->next = (*node)->next;
		free((*node)->content);
		free(*node);
		*node = before->next;
		return (1);
	}
	return (0);
}

int	unsetcmd(char **args, t_data *data)
{
	int		i;
	t_list	*env_head;
	t_list	*env_list;
	t_list	*before;

	i = -1;
	data->exitcode = 0;
	if (!args || !args[1])
		return (1);
	env_head = ft_string_to_lst(data->env);
	while (args[++i])
	{
		before = NULL;
		env_list = env_head;
		while (env_list)
		{
			if (removevar(before, &env_list, args[i]))
				break ;
			before = env_list;
			env_list = env_list->next;
		}
	}
	data->env = ft_lst_to_string(&env_head);
	return (1);
}
