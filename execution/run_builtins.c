/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:24:47 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/10 10:55:06 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	run_builtins(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "export") || !ft_strcmp(cmd[0], "/bin/export"))
		exportcmd(cmd, data);
	else if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "/bin/echo"))
		echocmd(cmd, data);
	else if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "/bin/env"))
		envcmd(cmd, data);
	else if (!ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "/bin/pwd"))
		pwdcmd(cmd, data);
	else if (!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "/bin/unset"))
		unsetcmd(cmd, data);
	else if (!ft_strcmp(cmd[0], "exit") || !ft_strcmp(cmd[0], "/bin/exit"))
		exitcmd(cmd, data);
	else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "/bin/cd"))
		cdcmd(cmd, data);
	else
		return (0);
	return (data->exitcode);
}

int	test_builtin(char **cmd)
{
	if (!ft_strcmp(cmd[0], "export") || !ft_strcmp(cmd[0], "/bin/export"))
		return (1);
	else if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "/bin/echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "/bin/env"))
		return (1);
	else if (!ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "/bin/pwd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "/bin/unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit") || !ft_strcmp(cmd[0], "/bin/exit"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "/bin/cd"))
		return (1);
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
	if (!test_builtin(cmd))
		return (0);
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
	data->exitcode = ret;
	return (1);
}
