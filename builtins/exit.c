/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:12:01 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/07 16:54:45 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minilib.h"

int ft_strisdigit(char *s)
{
	int 	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit((unsigned int)s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	exitcmd(char **args, t_data *data)
{
	data->exitcode = 1;
	if (args[1] && args[2])
	{
		ft_printf("minishell: exit: too many arguments\n", 2);
		data->exitcode = 1;
	}
	else if (args[1] && (ft_strisdigit(args[1]) == 0))
	{
		ft_printf("minishell: exit: %s numeric argument required", 2, args[1]);
		data->exitcode = 1;
	}
	else if (args[1])
		data->exitcode = ft_atoi(args[1]);
	else
		data->exitcode = 0;
	return (1);
}
