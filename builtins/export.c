/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:58:46 by ade-beco          #+#    #+#             */
/*   Updated: 2024/05/13 10:34:12 by ade-beco         ###   ########.fr       */
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
	new_env = malloc(i * sizeof(char *));
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

//static char	**delline_env(char **env, int index)
//{
//	char	**new_env;
//	int		i;

//	i = 0;
//	while (env[i++])
//		;
//	new_env = malloc((i - 1) * sizeof(char *));
//	if (!new_env)
//		exit(EXIT_FAILURE);
//	i = 0;
//	while (env[i])
//	{
//		if (i != index)
//		{
//			new_env[i] = malloc(sizeof(env[i]));
//			if (!new_env[i])
//				exit(EXIT_FAILURE);
//			new_env[i] = env[i];
//			i++;
//		}
//	}
//	return (new_env);
//}

static void	print_envvar(char **env)
{
	int		i;
	int		j;
	int		smaller;

	i = 1;
	j = 0;
	smaller = 0;
	while (env[i])
	{
		if (env[i][j] < env[smaller][j])
			smaller = i;
		else if (env[i][j] == env[smaller][j])
		{
			while (env[i][j] && env[smaller][j] && env[i][j] == env[smaller][j])
				j++;
			if (env[i][j] < env[smaller][j])
				smaller = i;
			j = 0;
		}
		i++;
	}
	ft_printf("%s\n", env[smaller]);
	env[smaller] = NULL;
	//print_envvar(env);
}

char	**exportcmd(char **args, char **env)
{
	//t_list	*env_list;
	char	**new_env;
	int		i;

	//init_env_list(env_list, env);
	if (!args[1])
		print_envvar(env);
	i = 0;
	new_env = addline_env(args[1], env);
	while (new_env[i])
	{
		ft_printf("%s\n", new_env[i++]);
	}
	return (new_env);
}
