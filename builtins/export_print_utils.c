/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:27:59 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/09 10:29:29 by ade-beco         ###   ########.fr       */
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

static void	print_linevar(char *var)
{
	int		i;
	char	*s;

	i = 0;
	while (var[i] && var[i] != '=')
		ft_printf("%c", 1, var[i++]);
	if (var[i] != '=')
	{
		ft_printf("\n", 1);
		return ;
	}
	s = ft_substr(var, i + 1, ft_strlen(var));
	ft_printf("=\"%s\"\n", 1, s);
	free (s);
}

void	print_envvar(t_list **env_list)
{
	t_list	*smallest;
	t_list	*biggest;
	t_list	*smaller;
	t_list	*temp;

	smallest = smallest_biggest_content(env_list, 1);
	biggest = smallest_biggest_content(env_list, -1);
	print_linevar(smallest->content);
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
		print_linevar(smaller->content);
		smallest = smaller;
	}
}