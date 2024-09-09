/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:29:24 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/09 11:28:29 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	find_env_var(char **envvars, char *var)
{
	int	i;

	i = 0;
	while (envvars[i])
	{
		if (!ft_strncmp(envvars[i], var, ft_strlen(envvars[i]) + 1))
		{
			free_array(envvars);
			return (i);
		}
		i++;
	}
	free_array(envvars);
	return (-1);
}

char	**get_env_vars(char **env, int i)
{
	char	**ret;
	int		y;

	while (env[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		crash_handler("Malloc\n");
	i = 0;
	while (env[i])
	{
		y = 0;
		while (env[i][y] != '=')
			y++;
		ret[i] = malloc(sizeof(char) * (y + 1));
		if (!ret[i])
			crash_handler("Malloc\n");
		y = -1;
		while (env[i][++y] != '=')
			ret[i][y] = env[i][y];
		ret[i++][y] = '\0';
	}
	ret[i] = 0;
	return (ret);
}

char	*get_env_var(char **env, char *var)
{
	int		i;
	char	*res;

	i = 0;
	if (!var || !var[0] || !env || !env[0])
		return (NULL);
	while ((env[i] && ft_strncmp(env[i], var, ft_strlen(var)))
		|| (env[i] && env[i][ft_strlen(var)] != '='))
		i++;
	if (env[i])
	{
		res = ft_strchr(env[i], '=');
		res++;
		res = ft_strdup(res);
		return (res);
	}
	return (NULL);
}
