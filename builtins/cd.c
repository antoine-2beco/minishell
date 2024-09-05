/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:40 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/03 15:35:15 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	change_cwd(char *folder, t_data *data)
{
	if (chdir(folder) == -1)
	{
		data->exitcode = 1;
		perror("minishell");
		return (1);
	}
	data->exitcode = 0;
	return (1);
}
