/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:40 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/10 09:27:59 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static int	handle_tilde(char **args, t_list *env, t_data *data)
{
	char	*tmp;

	if (args && args[1] && (!ft_strcmp(args[1], "~") || \
		!ft_strcmp(args[1], "--") || !ft_strcmp(args[1], "~/")))
	{
		tmp = get_env_var(data->env, "HOME");
		if (!tmp)
		{
			ft_printf("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		if (!ft_strcmp(args[1], "~/"))
			tmp = ft_strjoin(tmp, "/");
		free (args[1]);
		args[1] = tmp;
	}
	ft_printf("%s\n", 1, args[1]);
	(void)env;
	return (1);
}

int	cdcmd(char **args, t_data *data)
{
	t_list	*env_list;

	env_list = ft_string_to_lst(data->env);
	data->exitcode = 0;
	if (args && args[1] && args[2])
	{
		ft_printf("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	handle_tilde(args, env_list, data);
	free_array(data->env);
	data->env = ft_lst_to_string(&env_list);
	if (!data->env)
		crash_handler("malloc fail");
	free_list(env_list);
	return (1);
}
 // cd - change dir to old pwd and print pwd
 // changement general du pwd et du old pwd