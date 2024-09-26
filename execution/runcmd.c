/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:34:27 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/26 15:16:39 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	run_pipe(t_pipecmd *pcmd, t_data *data)
{
	int	fd[2];

	data->is_last_pipe = 0;
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	data->fd = fd;
	runcmd(pcmd->left, data, 1);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	data->is_last_pipe = is_last_pipe(pcmd);
	if (data->is_last_pipe)
	{
		dup2(data->stdout_cpy, STDOUT_FILENO);
		data->fd = NULL;
	}
	runcmd(pcmd->right, data, 1);
	dup2(data->stdin_cpy, STDIN_FILENO);
	close(data->stdin_cpy);
	close(data->stdout_cpy);
	if (is_last_pipe(pcmd))
		wait_pipes(data);
}

void	run_redir(t_redircmd *rcmd, t_data *data)
{
	int			stdred_cpy;
	int			ret;

	ret = 0;
	if (rcmd->cmd->type == REDIR)
		test_redi((t_redircmd *)rcmd->cmd, data, &ret, 0);
	if (ret)
		return ;
	stdred_cpy = dup(rcmd->fd);
	if (close(rcmd->fd) == -1)
		crash_handler("Close error\n");
	if (open(rcmd->file, rcmd->mode, 00644) < 0)
	{
		ft_printf("minishell: ", 2);
		perror(rcmd->file);
		data->exitcode = 1;
		dup2(stdred_cpy, rcmd->fd);
		return ;
	}
	while (rcmd->cmd->type == REDIR
		&& is_same_mode(((t_redircmd *)rcmd->cmd)->mode, rcmd->mode))
		rcmd = (t_redircmd *)rcmd->cmd;
	runcmd(rcmd->cmd, data, 0);
	dup2(stdred_cpy, rcmd->fd);
}

void	run_list(t_listcmd *lcmd, t_data *data)
{
	if (create_fork() == 0)
		runcmd(lcmd->left, data, 0);
	wait(0);
	runcmd(lcmd->right, data, 0);
}

void	run_heredoc(t_redircmd *rcmd, t_data *data)
{
	int	stdin_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	if (close(STDIN_FILENO) == -1)
		crash_handler("Close error\n");
	if (dup(rcmd->fd) == -1)
		crash_handler("Dup error\n");
	runcmd(rcmd->cmd, data, 0);
	dup2(stdin_cpy, STDIN_FILENO);
}

void	runcmd(t_cmd *cmd, t_data *data, int isInPipe)
{
	t_execcmd	*ecmd;

	if (cmd == 0)
		return ;
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (!ecmd->args || ecmd->args[0] == 0)
		{
			data->exitcode = 0;
			return ;
		}
		execution(ecmd->args, data, isInPipe, 0);
		return ;
	}
	else if (cmd->type == PIPE)
		run_pipe((t_pipecmd *)cmd, data);
	else if (cmd->type == REDIR)
		run_redir((t_redircmd *)cmd, data);
	else if (cmd->type == LIST)
		run_list((t_listcmd *)cmd, data);
	else if (cmd->type == HEREDOC)
		run_heredoc((t_redircmd *)cmd, data);
}
