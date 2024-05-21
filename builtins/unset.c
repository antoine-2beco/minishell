/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:26 by ade-beco          #+#    #+#             */
/*   Updated: 2024/05/21 17:01:25 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static t_list	*removevar(t_list *before, t_list *node)
{
	if (!node)
		return (NULL);
	if (!before)
	{
		before = node->next;
		free(node->content);
		free(node);
		return (before);
	}
	before->next = node->next;
	free(node->content);
	free(node);
	return (node);
}

char	**unsetcmd(char **args, char **env)
{
	int		i;
	t_list	*env_head;
	t_list	*env_list;
	t_list	*before;

	i = -1;
	env_head = ft_string_to_lst(env);
	while (args[++i])
	{
		before = NULL;
		env_list = env_head;
		while (env_list)
		{
			if (!ft_strncmp(env_list->content, ft_strjoin(args[i], "="), \
				ft_strlen(args[i])))
			{
				env_list = removevar(before, env_list);
				break ;
			}
			before = env_list;
			env_list = env_list->next;
		}
	}
	return (ft_lst_to_string(&env_head));
}
