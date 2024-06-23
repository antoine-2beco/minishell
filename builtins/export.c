/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:46 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/23 18:28:25 by ade-beco         ###   ########.fr       */
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
	ft_printf("%s\n", 1, smallest->content);
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
		ft_printf("%s\n", 1, smaller->content);
		smallest = smaller;
	}
}

int	check_name(char *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!args || !args[0] || args[0] == '=')
		return (0);
	while (args[i] != '\0' && args[i] != '=')
	{
		if (ft_isalpha(args[i]))
			j = 1;
		else
		{
			if (ft_isdigit(args[i]) && !j)
				return (0);
			else if (!ft_isdigit(args[i]) && args[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

int	exportcmd(char **args, t_data *data)
{
	t_list	*env_list;
	t_list	*node;
	int		i;

	i = 0;
	env_list = ft_string_to_lst(data->env);
	if (!args || !args[1])
		print_envvar(&env_list);
	while (args && args[1] && args[i++])
	{
		if (!check_name(args[i]))
			ft_printf("minishell: export: %s: not a valid identifier\n", 2, args[i]);
		else
		{
			node = ft_lstnew(args[i]);
			if (!node)
				exit(EXIT_FAILURE);
			ft_lstadd_back(&env_list, node);
			data->env = ft_lst_to_string(&env_list);
			if (!data->env)
				exit(EXIT_FAILURE);
		}
	}
	return (1);
}

//expor test => seg fault