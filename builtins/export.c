/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:46 by ade-beco          #+#    #+#             */
/*   Updated: 2024/04/15 12:23:07 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

static char	**addline_env(char *args, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i++])
		;
	new_env = malloc((i + 1) * sizeof(char *));
	if (!new_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		new_env[i] = malloc(sizeof(env[i]));
		if (!new_env[i])
			exit(EXIT_FAILURE);
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = malloc(sizeof(args));
	if (!new_env[i])
		exit (EXIT_FAILURE);
	new_env[i] = args;
	return (new_env);
}

char	**exportcmd(char **args, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = addline_env(args[1], env);
	while (new_env[i])
	{
		ft_printf("%s\n", new_env[i++]);
	}

	return (new_env);
}
