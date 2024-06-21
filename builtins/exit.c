/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:12:01 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/21 15:44:55 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minilib.h"

int	exitcmd(char **args, t_data *data)
{
	if (!args[1])
		data->exit = 1;
	else
		data->exit = ft_atoi(args[1]);
	return (1);
}
