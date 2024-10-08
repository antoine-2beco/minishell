/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:35:45 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/26 13:57:14 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	close_fd(t_data *data)
{
	if (data->fd)
	{
		close(data->fd[0]);
		close(data->fd[1]);
	}
}

void	child_exec(char *path, char **cmd, t_data *data)
{
	close_fd(data);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd, data->env);
	ft_printf("minishell: ", 2);
	perror(cmd[0]);
	free_array(cmd);
	free_array(data->env);
	exit(126);
}

void	ft_execve(char *path, char **cmd, t_data *data)
{
	int	pid;
	int	status;

	signal(SIGINT, sig_interrupt_exec);
	if (!ft_strcmp(cmd[0], "./minishell"))
		signal(SIGINT, SIG_IGN);
	pid = create_fork();
	if (!pid)
		child_exec(path, cmd, data);
	if (data->is_last_pipe)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exitcode = WEXITSTATUS(status);
	}
	else
		data->i++;
	signal(SIGINT, sig_interrupt);
}
