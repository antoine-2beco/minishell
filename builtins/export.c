/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:46 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/25 18:12:45 by hle-roi          ###   ########.fr       */
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

static void	print_envvar(t_list **env_list)
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

int	check_name(char *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!args || !args[0] || args[0] == '=')
		return (0);
	while (args[i] && args[i] != '=')
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

	i = 1;
	env_list = ft_string_to_lst(data->env);
	if (!args || !args[1])
	{
		print_envvar(&env_list);
		return (1);
	}
	while (args && args[i] && args[i])
	{
		if (!check_name(args[i]))
			break ;
		node = ft_lstnew(ft_strdup(args[i]));
		if (!node)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&env_list, node);
		i++;
	}
	free_array(data->env);
	data->env = ft_lst_to_string(&env_list);
	if (!data->env)
		exit(EXIT_FAILURE);
	free_list(env_list);
	return (1);
}
