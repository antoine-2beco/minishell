/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:02:55 by hle-roi           #+#    #+#             */
/*   Updated: 2024/05/22 14:10:42 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	pipex(t_cmd *cmd, char ***env)
{
	int			fd[2];
	t_pipecmd	*pcmd;
	int			i;

	i = 0;
	pcmd = (t_pipecmd *)cmd;
	if (pipe(fd) == -1)
		crash_handler("pipe\n");
	if (!create_fork())
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		runcmd(pcmd->left, env);
	}
	i++;
	while (pcmd->right->type == PIPE)
	{
		pcmd = (t_pipecmd *)pcmd->right;
		if (!create_fork())
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			runcmd(pcmd->left, env);
		}
		i++;
	}
	if (!create_fork())
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		runcmd(pcmd->right, env);
	}
	close(fd[0]);
	close(fd[1]);
	while (i-- >= 0)
		wait(0);
}
//enlever stdout_cpy