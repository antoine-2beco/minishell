/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:04:28 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/03 12:52:35 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	pwdcmd(char **args, t_data *data)
{
	int	i;

	(void)args;
	i = 0;
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
