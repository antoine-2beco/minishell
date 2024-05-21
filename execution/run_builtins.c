/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:24:47 by hle-roi           #+#    #+#             */
/*   Updated: 2024/05/21 13:50:45 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	is_builtin(char **cmd, char **env)
{
	if (!ft_strcmp(cmd[0], "export"))
		env = exportcmd(cmd, env);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echocmd(cmd));
	else if (!ft_strcmp(cmd[0], "env"))
		return (envcmd(cmd, env));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (pwdcmd(cmd, env));
	else if (!ft_strcmp(cmd[0], "unset"))
		env = unsetcmd(cmd, env);
	else
		return (0);
	return (1);
}

// catch option
