/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:17:26 by ade-beco          #+#    #+#             */
/*   Updated: 2024/05/21 13:54:33 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

char	**unsetcmd(char **args, char **env)
{
	int		i;
	t_list	*env_list;
	t_list	*temp;

	i = 0;
	if (!args[1])
		return (env);
	env_list = ft_string_to_lst(env);
	while (args[i])
	{
		temp = env_list;
		while (temp)
		{
			if (!ft_strncmp(temp->content, ft_strjoin(args[i], "="), \
				ft_strlen(args[i])))
			{
				ft_lstclear(&temp, NULL);
				break ;
			}
			temp = temp->next;
		}
		i++;
	}
	return (ft_lst_to_string(&env_list));
}

// maj var