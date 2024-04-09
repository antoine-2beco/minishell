/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:29:24 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/09 14:26:50 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	highest_num(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int	find_env_var(char **envvars, char *var)
{
	int	i;
	int	length;

	i = 0;
	while (envvars[i])
	{
		length = highest_num(ft_strlen(envvars[i]), ft_strlen(var));
		if (!ft_strncmp(envvars[i], var, length))
			return (i);
		i++;
	}
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
	i = 0;
	while (env[i])
	{
		y = 0;
		while (env[i][y] != '=')
			y++;
		ret[i] = malloc(sizeof(char) * (y + 1));
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

void	switch_inquote(char *ps, int *inquote)
{
	if (*ps == '\'' && !*inquote)
		*inquote = 1;
	else if (*ps == '\'' && *inquote)
		*inquote = 0;
}

char	*get_env_var(char *var, char **env)
{
	char	*str;
	int		i;

	i = find_env_var(get_env_vars(env), var);
	if (i == -1)
		return (NULL);
	str = env[i];
	str = &str[ft_strlen(var) + 1];
	return (str);
}
