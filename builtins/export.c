/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:46 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/23 13:11:17 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static int	check_name(char *args)
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

static int	snc(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)(c))
			return (i);
		i++;
	}
	if (s[i] == (char)(c))
		return (i);
	return (0);
}

static void	handle_var(t_data *data, t_list **env_list, char *va)
{
	t_list	*t;

	if (!check_name(va))
	{
		data->exitcode = 1;
		ft_printf("minishell: %s: not a valid identifier\n", 2, va);
		return ;
	}
	t = *env_list;
	while (t)
	{
		if ((snc(va, '=') && ft_strncmp(t->content, va, snc(va, '=')) == 0) || \
			(!snc(va, '=') && ft_strncmp(t->content, va, ft_strlen(va)) == 0))
		{
			if (snc(va, '='))
			{
				free(t->content);
				t->content = ft_strdup(va);
			}
			return ;
		}
		t = t->next;
	}
	ft_lstadd_back(env_list, ft_lstnewdup(va));
}

int	exportcmd(char **args, t_data *data)
{
	t_list	*env_list;
	int		i;

	i = 0;
	env_list = ft_string_to_lst(data->env);
	data->exitcode = 0;
	if (!args || !args[1])
		print_envvar(&env_list);
	while (args && args[++i])
	{
		handle_var(data, &env_list, args[i]);
		if (data->exitcode == 1)
			break ;
	}
	free_array(data->env);
	data->env = ft_lst_to_string(&env_list);
	if (!data->env)
		crash_handler("malloc fail");
	free_list(env_list);
	return (1);
}
