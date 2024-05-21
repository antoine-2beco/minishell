/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:46 by ade-beco          #+#    #+#             */
/*   Updated: 2024/05/21 16:22:51 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static t_list	*smallest_biggest_content(t_list **lst, int param)
{
	t_list	*smallest_biggest;
	t_list	*temp;

	temp = *lst;
	smallest_biggest = temp;
	while (temp)
	{
		if (ft_strsmaller(smallest_biggest->content, temp->content) == param)
			smallest_biggest = temp;
		temp = temp->next;
	}
	return (smallest_biggest);
}

static void	print_envvar(t_list **env_list)
{
	t_list	*smallest;
	t_list	*biggest;
	t_list	*smaller;
	t_list	*temp;

	smallest = smallest_biggest_content(env_list, 1);
	biggest = smallest_biggest_content(env_list, -1);
	ft_printf("%s\n", smallest->content);
	while (biggest != smallest)
	{
		temp = *env_list;
		smaller = biggest;
		while (temp)
		{
			if (ft_strsmaller(smallest->content, temp->content) == -1 \
				&& ft_strsmaller(smaller->content, temp->content) == 1)
				smaller = temp;
			temp = temp->next;
		}
		ft_printf("%s\n", smaller->content);
		smallest = smaller;
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
