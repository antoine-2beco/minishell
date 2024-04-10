/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:02:55 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/10 13:30:59 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	pipex(t_cmd *cmd, int stdout_cpy, char **env)
{
	int			p[2];
	t_pipecmd	*pcmd;
	int			pid[100];
	int			i;

	i = 0;
	pcmd = (t_pipecmd *)cmd;
	if (pipe(p) == -1)
		crash_handler("pipe\n");
	pid[i] = create_fork();
	if (!pid[i])
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		runcmd(pcmd->left, env, stdout_cpy);
	}
	i++;
	while (pcmd->right->type == PIPE)
	{
		pcmd = (t_pipecmd *)pcmd->right;
		pid[i] = create_fork();
		if (!pid[i])
		{
			dup2(p[0], STDIN_FILENO);
			dup2(p[1], STDOUT_FILENO);
			runcmd(pcmd->left, env, stdout_cpy);
		}
		i++;
	}
	pid[i] = create_fork();
	if (!pid[i])
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		dup2(stdout_cpy, STDOUT_FILENO);
		runcmd(pcmd->right, env, stdout_cpy);
	}
	while (i-- >= 0)
		wait(0);
}
