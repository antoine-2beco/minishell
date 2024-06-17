/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:48:26 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/17 13:47:30 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T' && env[i][3] == 'H')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*str;
	char	**paths;
	char	*exec;

	i = 0;
	str = env[find_path(env)];
	str = &str[5];
	paths = ft_split(str, ':');
	while (paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(str, cmd);
		free(str);
		if (access(exec, F_OK | X_OK) == 0)
		{
			return (exec);
		}
		free(exec);
		i++;
	}
	return (cmd);
}

void	execution(char **cmd, t_data *data)
{
	char	*path;

	if (cmd[0] == 0)
	{
		ft_putstr_fd("minishell: permission denied: \n", 2);
		exit(EXIT_FAILURE);
	}
	if (is_builtin(cmd, data))
		;
	else if (data->env[0] != NULL)
	{
		path = get_path(cmd[0], data->env);
		signal(SIGQUIT, SIG_DFL);
		if (!create_fork())
		{
			execve(path, cmd, data->env);
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putchar_fd('\n', 2);
			exit(127);
		}
		wait(0);
	}
}

void	runcmd(t_cmd *cmd, t_data *data)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	t_listcmd	*lcmd;
	t_pipecmd	*pcmd;
	int			fd[2];
	int			stdin_cpy;
	int			stdout_cpy;

	if (cmd == 0)
		exit(1);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->args[0] == 0)
			return ;
		execution(ecmd->args, data);
		return ;
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		stdin_cpy = dup(STDIN_FILENO);
		stdout_cpy = dup(STDOUT_FILENO);
		if (pipe(fd) == -1)
			crash_handler("pipe\n");
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		runcmd(pcmd->left, data);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(stdout_cpy, STDOUT_FILENO);
		runcmd(pcmd->right, data);
		dup2(stdin_cpy, STDIN_FILENO);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode, 00644) < 0)
			crash_handler("open %s failed\n");
		while (rcmd->cmd->type == REDIR)
			rcmd = (t_redircmd *)rcmd->cmd;
		runcmd(rcmd->cmd, data);
	}
	else if (cmd->type == LIST)
	{
		lcmd = (t_listcmd *)cmd;
		if (create_fork() == 0)
			runcmd(lcmd->left, data);
		wait(0);
		runcmd(lcmd->right, data);
	}
	else if (cmd->type == HEREDOC)
	{
		rcmd = (t_redircmd *)cmd;
		close(0);
		dup(rcmd->fd);
		runcmd(rcmd->cmd, data);
	}
}
