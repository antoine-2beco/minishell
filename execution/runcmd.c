/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:34:27 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/10 14:46:55 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	run_pipe(t_pipecmd *pcmd, t_data *data)
{
	int	stdout_cpy;
	int	stdin_cpy;
	int	fd[2];

	stdin_cpy = dup(STDIN_FILENO);
	stdout_cpy = dup(STDOUT_FILENO);
	if (stdin_cpy == -1 || stdout_cpy == -1)
		crash_handler("Dup error\n");
	if (pipe(fd) == -1)
		crash_handler("pipe error\n");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		crash_handler("Dup2 error\n");
	if (close(fd[1]) == -1)
		crash_handler("Close error\n");
	runcmd(pcmd->left, data, 1);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		crash_handler("Dup2 error\n");
	if (close(fd[0]) == -1)
		crash_handler("Close error\n");
	if (dup2(stdout_cpy, STDOUT_FILENO) == -1)
		crash_handler("Dup2 error\n");
	runcmd(pcmd->right, data, 1);
	if (dup2(stdin_cpy, STDIN_FILENO) == -1)
		crash_handler("Dup2 error\n");
}

void	test_redi(t_redircmd *redir, t_data *data, int *ret)
{
	int	fd;

	if (redir->cmd->type != REDIR)
	{
		fd = open(redir->file, redir->mode, 00644);
		if (fd < 0)
		{
			ft_printf("minishell: ", 2);
			perror(redir->file);
			data->exitcode = 1;
			*ret = 1;
			return ;
		}
		close(fd);
		*ret = 0;
		return ;
	}
	else
		test_redi((t_redircmd *)redir->cmd, data, ret);
	if (*ret == 1)
		return ;
	fd = open(redir->file, redir->mode, 00644);
	if (fd < 0)
	{
		ft_printf("minishell: ", 2);
		perror(redir->file);
		data->exitcode = 1;
		*ret = 1;
		return ;
	}
	close(fd);
	return ;
}

int	is_same_mode(int mode1, int mode2)
{
	if (mode1 == O_RDONLY && mode2 == O_RDONLY)
		return (1);
	else if (mode1 == O_RDONLY && mode2 != O_RDONLY)
		return (0);
	else if (mode1 != O_RDONLY && mode2 == O_RDONLY)
		return (0);
	else
		return (1);
}

void	run_redir(t_redircmd *rcmd, t_data *data)
{
	int			stdred_cpy;
	int			ret;

	ret = 0;
	if (rcmd->cmd->type == REDIR)
		test_redi((t_redircmd *)rcmd->cmd, data, &ret);
	if (ret)
		return ;
	//execution de la redirection
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
	while (rcmd->cmd->type == REDIR && is_same_mode(((t_redircmd *)rcmd->cmd)->mode, rcmd->mode))
	{
		rcmd = (t_redircmd *)rcmd->cmd;
	}
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
		if (ecmd->args[0] == 0)
		{
			data->exitcode = 0;
			return ;
		}
		execution(ecmd->args, data, isInPipe);
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
