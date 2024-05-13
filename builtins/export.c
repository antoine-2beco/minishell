/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:46 by ade-beco          #+#    #+#             */
/*   Updated: 2024/05/13 15:41:55 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static void	print_envvar(t_list **env_list)
{
	t_list	*temp;

	temp = *env_list;
	while (temp)
	{
		ft_printf("%s\n", temp->content);
		temp = temp->next;
	}

}

char	**exportcmd(char **args, char **env)
{
	int		i;
	t_list	*env_list;
	t_list	*node;

	i = 0;
	env_list = ft_string_to_lst(env);
	if (!args[1])
		print_envvar(&env_list);
	else
	{
		node = ft_lstnew(args[1]);
		if (!node)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&env_list, node);
		print_envvar(&env_list);
		env = ft_lst_to_string(&env_list);
		if (!env)
			exit(EXIT_FAILURE);
	}
	return (env);
}
