/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:04:28 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/12 13:51:57 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	pwdcmd(char **args, char **env)
{
	int	i;

	i = 0;
	if (args[1])
		return (0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			ft_printf("%s\n", 1, ft_strtrim(env[i], "PWD="));
			break ;
		}
		i++;
	}
	return (1);
}
