/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:40 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/10 11:19:01 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

// 7 for OLDPWD / 4 for PWD
static int	update_oldpwd(t_list *env, char *pwd, int len)
{
	char	*tmp;

	while (env)
	{
		if ((len == 7 && !ft_strncmp(env->content, "OLDPWD=", len)) \
			|| (len == 4 && !ft_strncmp(env->content, "PWD=", len)))
		{
			tmp = ft_substr(env->content, 0, len);
			free (env->content);
			env->content = ft_strjoin(tmp, pwd);
			free (tmp);
			free (pwd);
			return (1);
		}
		env = env->next;
	}
	if (len == 7)
		ft_printf("minishell: cd: OLDPWD not set\n", 2);
	if (len == 4)
		ft_printf("minishell: cd: PWD not set\n", 2);
	free (pwd);
	return (1);
}

static int	set_directory(char *arg, t_list *env, t_data *data)
{
	if (!update_oldpwd(env, get_env_var(data->env, "PWD"), 7))
		return (1);
	(void)arg;
	return (1);
}

static int	handle_s_dash(char *arg, t_list *env, t_data *data)
{
	char	*tmp;

	if (arg && !ft_strcmp(arg, "-"))
	{
		tmp = get_env_var(data->env, "OLDPWD");
		if (!tmp)
		{
			ft_printf("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		free(arg);
		arg = ft_strdup(tmp);
		free(tmp);
		set_directory(arg, env, data);
		tmp = get_env_var(data->env, "PWD");
		if (!tmp)
		{
			ft_printf("minishell: cd: PWD not set\n", 2);
			return (1);
		}
		ft_printf("%s\n", 1, tmp);
		free (tmp);
		return (1);
	}
	return (set_directory(arg, env, data));
}

static int	handle_tilde(char *arg, t_list *env, t_data *data)
{
	char	*tmp;

	if (!ft_strcmp(arg, "~") || !ft_strcmp(arg, "--") \
		|| !ft_strcmp(arg, "~/"))
	{
		tmp = get_env_var(data->env, "HOME");
		if (!tmp)
		{
			ft_printf("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		if (!ft_strcmp(arg, "~/"))
		{
			free (arg);
			arg = ft_strjoin(tmp, "/");
		}
		else
			arg = ft_strdup(tmp);
		free (tmp);
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
	{
		ft_printf("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (args[1])
		arg = ft_strdup(args[1]);
	else
		arg = ft_strdup("~");
	handle_tilde(arg, env_list, data);
	free_array(data->env);
	data->env = ft_lst_to_string(&env_list);
	if (!data->env)
		crash_handler("malloc fail");
	free_list(env_list);
	//free (arg);
	return (1);
}
// changement general du pwd et du old pwd