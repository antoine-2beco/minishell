/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:48:26 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/19 11:10:27 by hle-roi          ###   ########.fr       */
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
	free(str);
	i = -1;
	while (paths[++i])
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
	}
	free_array(paths);
	return (NULL);
}

int	is_directory(char **cmd, t_data *data)
{
	struct stat	*buff;

	buff = malloc(sizeof(struct stat));
	if (!buff)
		crash_handler("Malloc");
	stat(cmd[0], buff);
	if (S_ISDIR(buff->st_mode))
	{
		ft_printf("minishell: %s: is a directory\n", 2, cmd[0]);
		data->exitcode = 126;
		free(buff);
		return (1);
	}
	return (0);
	free(buff);
}

int	check_directory(char **cmd, t_data *data, char **path)
{
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
	{
		if (access(cmd[0], F_OK | X_OK) != -1)
		{
			if (is_directory(cmd, data))
				return (1);
			ft_execve(cmd[0], cmd, data);
			return (1);
		}
		ft_printf("minishell: %s: %s\n", 2, cmd[0], strerror(errno));
		if (access(cmd[0], F_OK) == -1)
			data->exitcode = 127;
		else
			data->exitcode = 126;
		return (1);
	}
	else
		*path = get_path(cmd[0], data->env);
	return (0);
}

int	check_path(char *path, t_data *data, char **cmd)
{
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", 2, cmd[0]);
		data->exitcode = 127;
		return (1);
	}
	return (0);
}

void	execution(char **cmd, t_data *data, int IsInPipe, char *path)
{
	if (is_builtin(cmd, data, IsInPipe))
		return ;
	else if (data->env && data->env[0] != NULL)
	{
		if (check_directory(cmd, data, &path))
			return ;
		if (check_path(path, data, cmd))
			return ;
		ft_execve(path, cmd, data);
		free(path);
	}
}
