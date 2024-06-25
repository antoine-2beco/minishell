/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:48:26 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/25 16:50:20 by hle-roi          ###   ########.fr       */
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

	i = find_path(env);
	if (i == -1)
		return (NULL);
	str = env[i];
	str = &str[5];
	paths = ft_split(str, ':');
	i = 0;
	while (paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(str, cmd);
		free(str);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (exec);
		}
		free(exec);
		i++;
	}
	free_array(paths);
	if (cmd[0] == '.' && cmd[1] == '/')
		return (cmd);
	return (NULL);
}

void	execution(char **cmd, t_data *data)
{
	char		*path;
	int			pid;
	int			status;
	struct stat	*buff;

	path = 0;
	if (is_builtin(cmd, data))
		return ;
	else if (data->env[0] != NULL)
	{
		path = get_path(cmd[0], data->env);
		if (!path)
		{
			ft_printf("minishell: %s: command not found\n", 2, cmd[0]);
			data->exitcode = 127;
			return ;
		}
		buff = malloc(sizeof(struct stat));
		if (!buff)
			crash_handler("Malloc");
		stat(cmd[0], buff);
		if (S_ISDIR(buff->st_mode))
		{
			ft_printf("minishell: %s: is a directory\n", 2, cmd[0]);
			data->exitcode = 126;
			free(buff);
			return ;
		}
		free(buff);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, sig_interrupt_exec);
		pid = create_fork();
		if (!pid)
		{
			execve(path, cmd, data->env);
			ft_printf("minishell: ", 2);
			perror(cmd[0]);
			ft_printf("%d\n", errno);
			exit(126);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exitcode = WEXITSTATUS(status);
		free(path);
		signal(SIGINT, sig_interrupt);
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
	int			stdred_cpy;

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
		execution(ecmd->args, data);
		return ;
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
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
		runcmd(pcmd->left, data);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			crash_handler("Dup2 error\n");
		if (close(fd[0]) == -1)
			crash_handler("Close error\n");
		if (dup2(stdout_cpy, STDOUT_FILENO) == -1)
			crash_handler("Dup2 error\n");
		runcmd(pcmd->right, data);
		if (dup2(stdin_cpy, STDIN_FILENO) == -1)
			crash_handler("Dup2 error\n");
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		stdred_cpy = dup(rcmd->fd);
		if (close(rcmd->fd) == -1)
			crash_handler("Close error\n");
		if (open(rcmd->file, rcmd->mode, 00644) < 0)
			crash_handler("open failed\n");
		while (rcmd->cmd->type == REDIR)
			rcmd = (t_redircmd *)rcmd->cmd;
		runcmd(rcmd->cmd, data);
		dup2(stdred_cpy, rcmd->fd);
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
		stdin_cpy = dup(STDIN_FILENO);
		if (close(STDIN_FILENO) == -1)
			crash_handler("Close error\n");
		if (dup(rcmd->fd) == -1)
			crash_handler("Dup error\n");
		runcmd(rcmd->cmd, data);
		dup2(stdin_cpy, STDIN_FILENO);
	}
}
