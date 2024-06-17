/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:04:28 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/17 13:51:50 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	pwdcmd(char **args, t_data *data)
{
	int	i;

	i = 0;
	if (args[1])
		return (0);
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PWD=", 4))
		{
			ft_printf("%s\n", 1, ft_strtrim(data->env[i], "PWD="));
			break ;
		}
		i++;
	}
	return (1);
}
