/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:12:01 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/03 15:02:15 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minilib.h"

int	exitcmd(char **args, t_data *data)
{
	if (!args[1])
		data->exitcode = 1;
	else
		data->exitcode = ft_atoi(args[1]);
	return (1);
}
