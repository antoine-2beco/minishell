/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:24:47 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/10 08:35:41 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	run_builtins(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "export") || !ft_strcmp(cmd[0], "/bin/export"))
		return (exportcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "/bin/echo"))
		return (echocmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "/bin/env"))
		return (envcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "/bin/pwd"))
		return (pwdcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "/bin/unset"))
		return (unsetcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "exit") || !ft_strcmp(cmd[0], "/bin/exit"))
		return (exitcmd(cmd, data));
	else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "/bin/cd"))
		return (cdcmd(cmd, data));
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
