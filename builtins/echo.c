/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:48:21 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/25 09:50:57 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static void	print_chars(char **args, int n_flag)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!(args[i][j] == '\n' && n_flag) && !(i == 1 && j < n_flag))
				ft_printf("%c", 1, args[i][j]);
			j++;
		}
		if (args[i + 1] && args[i][0] != '\0' && !(i == 1 && n_flag))
			write(1, " ", 1);
		i++;
	}
}

static int	flag_check(char *arg)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i] && arg[i] == 'n')
	{
		n_flag = 2;
		i++;
	}
	if (!arg[i] && n_flag == 2)
		return (i);
	while ((arg[i] == ' ') || (arg[i] == '\t') || (arg[i] == '\n')
		|| (arg[i] == '\v') || (arg[i] == '\f') || (arg[i] == '\r'))
	{
		i++;
		n_flag = 3;
	}
	if (n_flag == 3)
		return (i);
	return (0);
}

int	echocmd(char **args, t_data *data)
{
	int		n_flag;

	if (!args[1])
	{
		write(1, "\n", 1);
		data->exitcode = 0;
		return (1);
	}
	n_flag = flag_check(args[1]);
	print_chars(args, n_flag);
	if (!n_flag)
		write(1, "\n", 1);
	data->exitcode = 0;
	return (1);
}
