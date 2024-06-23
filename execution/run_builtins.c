/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:24:47 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/23 17:53:01 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	is_builtin(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "export"))
		return (exportcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echocmd(cmd));
	else if (!ft_strcmp(cmd[0], "env"))
		return (envcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (pwdcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (unsetcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (exitcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "cd"))
		return (change_cwd(cmd[1]));
	else
		return (0);
	return (1);
}
