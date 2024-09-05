/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:24:47 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/05 13:14:24 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"


int	run_builtins(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "export"))
		return (exportcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echocmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "env"))
		return (envcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (pwdcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (unsetcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (exitcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "cd"))
		return (change_cwd(cmd[1], data));
	else
		return (0);
	return (1);
}

int	is_builtin(char **cmd, t_data *data, int IsInPipe)
{
	int	pid;
	int	status;
	int	ret;

	ret = 0;
	if (IsInPipe)
	{
		pid = create_fork();
		if (!pid)
			exit(run_builtins(cmd, data));
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	else
		ret = run_builtins(cmd, data);
	return (ret);
}
