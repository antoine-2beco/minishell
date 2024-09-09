/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:48:21 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/09 10:26:33 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static void	print_chars(char **args, int i, int n_flag)
{
	int	j;

	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] != '\n' || !n_flag)
				ft_printf("%c", 1, args[i][j++]);
			else if (n_flag)
				j++;
		}
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
}

int	echocmd(char **args, t_data *data)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (!args[1])
	{
		write(1, "\n", 1);
		data->exitcode = 0;
		return (1);
	}
	if (args[1][0] && args[1][1] && args[1][0] == '-' && args[1][1] != 'n')
		return (0);
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
		n_flag = i++;
	print_chars(args, i, n_flag);
	if (!n_flag)
		write(1, "\n", 1);
	data->exitcode = 0;
	return (1);
}
