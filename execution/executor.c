/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:48:26 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:01 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*str;
	char	**paths;
	char	*exec;

	str = get_env_var(env, "PATH");
	if (!str)
		return (NULL);
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
		return (ft_strdup(cmd));
	return (NULL);
}

void	execution(char **cmd, t_data *data, int IsInPipe)
{
	char		*path;
	int			pid;
	int			status;
	struct stat	*buff;

	path = 0;
	if (is_builtin(cmd, data, IsInPipe))
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
			exit(126);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exitcode = WEXITSTATUS(status);
		free(path);
		signal(SIGINT, sig_interrupt);
	}
}
