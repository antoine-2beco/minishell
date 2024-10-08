/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:40 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/20 09:03:48 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

// 7 for OLDPWD / 4 for PWD
static int	update_oldpwd(t_list *env, int len)
{
	char	*tmp;
	char	cwd[PATH_MAX];

	while (env)
	{
		if ((len == 7 && !ft_strncmp(env->content, "OLDPWD=", len)) \
			|| (len == 4 && !ft_strncmp(env->content, "PWD=", len)))
		{
			tmp = ft_substr(env->content, 0, len);
			if (!getcwd(cwd, PATH_MAX))
			{
				free(tmp);
				return (1);
			}
			free(env->content);
			env->content = ft_strjoin(tmp, cwd);
			free(tmp);
			return (1);
		}
		env = env->next;
	}
	return (1);
}

static int	set_directory(char *arg, t_list *env, t_data *data)
{
	if (!update_oldpwd(env, 7))
		return (free(arg), 1);
	if (chdir(arg) == -1)
	{
		free (arg);
		data->exitcode = 1;
		perror("minishell");
		return (1);
	}
	update_oldpwd(env, 4);
	free(arg);
	return (1);
}

static int	handle_s_dash(char *arg, t_list *env, t_data *data)
{
	char	*tmp;

	if (arg && !ft_strcmp(arg, "-"))
	{
		tmp = get_env_var(data->env, "OLDPWD");
		free(arg);
		if (!tmp)
			return (perror("minishell"), 1);
		arg = ft_strdup(tmp);
		free(tmp);
		set_directory(arg, env, data);
		tmp = get_env_var(data->env, "PWD");
		if (!tmp)
			return (perror("minishell"), 1);
		ft_printf("%s\n", 1, arg);
		free(tmp);
		return (1);
	}
	return (set_directory(arg, env, data));
}

static int	handle_tilde(t_data *data, t_list *env, char *arg)
{
	char	*tmp[2];

	if (!ft_strcmp(arg, "~") || !ft_strcmp(arg, "--") \
		|| !ft_strncmp(arg, "~/", 2))
	{
		tmp[0] = get_env_var(data->env, "HOME");
		if (!tmp[0])
			return (perror("minishell"), 1);
		if (!ft_strncmp(arg, "~/", 2))
		{
			tmp[1] = ft_substr(arg, 1, ft_strlen(arg));
			free (arg);
			arg = ft_strjoin(tmp[0], tmp[1]);
			free(tmp[1]);
		}
		else
		{
			free(arg);
			arg = ft_strdup(tmp[0]);
		}
		free(tmp[0]);
	}
	return (handle_s_dash(arg, env, data));
}

int	cdcmd(char **args, t_data *data)
{
	t_list	*env_list;
	char	*arg;

	env_list = ft_string_to_lst(data->env);
	data->exitcode = 0;
	if (args && args[1] && args[2])
		return (1);
	if (args[1])
		arg = ft_strdup(args[1]);
	else
		arg = ft_strdup("~");
	handle_tilde(data, env_list, arg);
	free_array(data->env);
	data->env = ft_lst_to_string(&env_list);
	if (!data->env)
		crash_handler("malloc fail");
	free_list(env_list);
	return (1);
}
