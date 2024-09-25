/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:12:01 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/25 10:05:55 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	ft_strisdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit((unsigned int)s[i]) == 0 && s[i] != '-' \
			&& s[i] != '+' && s[i] != '\"')
			return (0);
		i++;
	}
	return (1);
}

int	exitcmd(char **args, t_data *data)
{
	long long int	i;

	if (args[1] && (ft_strisdigit(args[1]) == 0))
	{
		ft_printf("exit\n", 1);
		ft_printf("minishell: exit: numeric argument required\n", 2, args[1]);
		data->exitcode = 255;
	}
	else if (args[1] && args[2])
	{
		ft_printf("exit\n", 1);
		ft_printf("minishell: exit: too many arguments\n", 2);
		data->exitcode = 1;
		return (1);
	}
	else if (args[1])
	{
		i = ft_atoi(args[1]);
		if (i < 0 || i > 255)
			data->exitcode = ((i % 256) + 256) % 256;
		else
			data->exitcode = i;
	}
	data->exit = 1;
	return (1);
}
