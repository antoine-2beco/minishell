/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:29:24 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/18 14:02:08 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	find_env_var(char **envvars, char *var)
{
	int	i;

	i = 0;
	while (envvars[i])
	{
		if (!ft_strncmp(envvars[i], var, ft_strlen(envvars[i]) + 1))
			return (i);
		i++;
	}
	free_array(envvars);
	return (-1);
}

char	**get_env_vars(char **env)
{
	char	**ret;
	int		i;
	int		y;

	i = 0;
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
		y = 0;
		while (env[i][y] != '=')
		{
			ret[i][y] = env[i][y];
			y++;
		}
		ret[i++][y] = '\0';
	}
	ret[i] = 0;
	return (ret);
}

char	*get_env_var(char *var, t_data *data)
{
	char	*str;
	int		i;

	if (!ft_strcmp(var, "?"))
	{
		str = ft_itoa(data->exitcode);
		return (str);
	}
	i = find_env_var(get_env_vars(data->env), var);
	if (i == -1)
		return (NULL);
	str = data->env[i];
	str = &str[ft_strlen(var) + 1];
	return (str);
}
