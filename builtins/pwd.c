/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:04:28 by ade-beco          #+#    #+#             */
/*   Updated: 2024/09/03 14:54:30 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	pwdcmd(char **args, t_data *data)
{
	char	path[100];

	(void)args;
	if (!getcwd(path, sizeof(path)))
	{
		perror("minishell");
		data->exitcode = 1;
		return (1);
	}
	ft_printf("%s\n", 1, path);
	data->exitcode = 0;
	return (1);
}
