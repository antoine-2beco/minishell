/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:45:59 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/12 13:51:48 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	envcmd(char **args, char **env)
{
	int	i;

	if (args && args[1])
		return (0);
	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", 1, env[i++]);
	}
	return (1);
}
