/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:51:34 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/20 11:54:51 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	is_last_pipe(t_pipecmd *pcmd)
{
	if (pcmd->right->type == PIPE)
		return (0);
	return (1);
}

void	wait_pipes(t_data *data)
{
	while (data->i-- > 0)
		wait(0);
}
