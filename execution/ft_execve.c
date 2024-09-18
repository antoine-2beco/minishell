/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:35:45 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/18 12:53:15 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	ft_execve(char *path, char **cmd, t_data *data)
{
	int	pid;
	int	status;

	signal(SIGINT, sig_interrupt_exec);
	pid = create_fork();
	if (!pid)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd, data->env);
		ft_printf("minishell: ", 2);
		perror(cmd[0]);
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exitcode = WEXITSTATUS(status);
	signal(SIGINT, sig_interrupt);
}
