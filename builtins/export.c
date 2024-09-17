/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:46 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/17 15:14:03 by ade-beco         ###   ########.fr       */
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

static int	strnchr(const char *s, int c)
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

static void	handle_var(t_data *data, t_list **env_list, char *arg)
{
	t_list	*temp;
	t_list	*node;

	if (!check_name(arg))
	{
		data->exitcode = 1;
		ft_printf("minishell: %s: not a valid identifier\n", 2, arg);
		return ;
	}
	temp = *env_list;
	while (temp)
	{
		if (ft_strncmp(temp->content, arg, strnchr(arg, '=') + 1) == 0)
		{
			free(temp->content);
			temp->content = ft_strdup(arg);
			return ;
		}
		temp = temp->next;
	}
	node = ft_lstnewdup(arg);
	if (!node)
		crash_handler("Malloc Fail");
	ft_lstadd_back(env_list, node);
}

int	exportcmd(char **args, t_data *data)
{
	t_list	*env_list;
	int		i;
	char	*arg;

	i = 0;
	env_list = ft_string_to_lst(data->env);
	data->exitcode = 0;
	if (!args || !args[1])
		print_envvar(&env_list);
	while (args && args[++i])
	{
		if (!strnchr(args[i], '='))
			arg = ft_strjoin(args[i], "=");
		else
			arg = ft_strdup(args[i]);
		handle_var(data, &env_list, arg);
		free (arg);
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
