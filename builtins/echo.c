/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:48:21 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/12 14:05:22 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

//int	echocmd(char **args)
//{
//	int		i;
//	int		j;

//	i = 1;
//	if (!args[1] \
//		|| (args[1][0] && args[1][1] && args[1][0] == '-' && args[1][1] != 'n'))
//		return (0);
//	else if (args[1][0] && args[1][1] && args[1][0] == '-' && args[1][1] == 'n')
//	{
//		while (args[++i])
//		{
//			j = 0;
//			while (args[i][j])
//			{
//				if (args[i][j] != '\n')
//					ft_printf("%c", args[i][j++]);
//			}
//		}
//	}
//	else
//		while (args[i])
//			ft_printf("%s ", args[i++]);
//	ft_printf("\n");
//	return (1);
//}

int	echocmd(char **args)
{
	int		i;
	int		j;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (1);
	}
	if (args[1][0] && args[1][1] && args[1][0] == '-' && args[1][1] != 'n')
		return (0);
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
		n_flag = i++;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\\')
			{
				if (args[i][j + 1] == '\0')
					write(1, " ", 1);
				j++;
			}
			else if (args[i][j] != '\n' && !n_flag)
				ft_printf("%c", 1, args[i][j++]);
		}
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (1);
}

// Pas possible de mettre des /n dans la console
// Je ne recois que arg par arg donc pas les espaces tabs ou autre entre chaque arg
