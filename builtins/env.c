/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:45:59 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/25 15:10:58 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	envcmd(char **args, t_data *data)
{
	int	i;

	if (args && args[1])
		return (0);
	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			ft_printf("%s\n", 1, data->env[i]);
		i++;
	}
	return (1);
}
