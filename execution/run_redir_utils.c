/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:38:26 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/13 12:40:03 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	redir_error(t_redircmd *redir, t_data *data, int *ret)
{
	ft_printf("minishell: ", 2);
	perror(redir->file);
	data->exitcode = 1;
	*ret = 1;
}

void	test_redi(t_redircmd *redir, t_data *data, int *ret, int fd)
{
	if (redir->cmd->type != REDIR)
	{
		fd = open(redir->file, redir->mode, 00644);
		if (fd < 0)
		{
			redir_error(redir, data, ret);
			return ;
		}
		close(fd);
		*ret = 0;
		return ;
	}
	else
		test_redi((t_redircmd *)redir->cmd, data, ret, 0);
	if (*ret == 1)
		return ;
	fd = open(redir->file, redir->mode, 00644);
	if (fd < 0)
	{
		redir_error(redir, data, ret);
		return ;
	}
	close(fd);
	return ;
}

int	is_same_mode(int mode1, int mode2)
{
	if (mode1 == O_RDONLY && mode2 == O_RDONLY)
		return (1);
	else if (mode1 == O_RDONLY && mode2 != O_RDONLY)
		return (0);
	else if (mode1 != O_RDONLY && mode2 == O_RDONLY)
		return (0);
	else
		return (1);
}
