/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:13:09 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/25 12:01:52 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

int	create_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		crash_handler("Error Fork\n");
	return (pid);
}

t_cmd	*parsecmd(char *s, t_data *data)
{
	char	*es;
	t_cmd	*cmd;

	if (!s)
		return (NULL);
	if (!s[0])
		return (NULL);
	es = s + ft_strlen(s);
	if (check_syntax(&s, es, data))
		return (NULL);
	cmd = parseline(&s, es, data);
	peek(&s, es, " ");
	if (s != es)
		crash_handler("synthax : ';' not allowed\n");
	return (cmd);
}

static int	shlvl_update(char **env, int i, int shlvl)
{
	int		j;
	int		k;
	char	*temp;

	j = 0;
	while (shlvl == 0 && env[j])
	{
		if (!ft_strncmp(env[j], "SHLVL=", 6))
		{
			free(env[j]);
			k = ft_atoi(env[j] + 6);
			if (k == INT32_MIN)
			{
				env[j] = ft_strdup("SHLVL=1");
				return (i);
			}
			temp = ft_itoa(k + 1);
			env[j] = ft_strjoin("SHLVL=", temp);
			free(temp);
			return (i);
		}
		j++;
	}
	env[i] = ft_strdup("SHLVL=1");
	return (i + 1);
}

static char	**cpy_env(char **pre_env)
{
	char	**env;
	int		i;
	int		shlvl;

	i = -1;
	shlvl = 1;
	while (pre_env[++i])
		if (!ft_strncmp(pre_env[i], "SHLVL=", 6))
			shlvl = 0;
	env = malloc((i + shlvl + 1) * sizeof(char *));
	if (!env)
		crash_handler("Error Malloc\n");
	i = -1;
	while (pre_env[++i])
	{
		env[i] = ft_strdup(pre_env[i]);
		if (!env[i])
			crash_handler("Error Malloc\n");
	}
	i = shlvl_update(env, i, shlvl);
	env[i] = 0;
	return (env);
}

int	main(int argc, char **argv, char **pre_env)
{
	char	*line;
	t_data	data;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	data.exitcode = 0;
	data.exit = 0;
	disable_signal_print();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_interrupt);
	data.env = cpy_env(pre_env);
	line = "1";
	while (line > 0 && !data.exit)
	{
		init_data(&data);
		line = readline("\e[1m\x1b[36mMinishell ➤ \x1b[36m\e[m");
		add_history(line);
		cmd = expand(parsecmd(line, &data), &data);
		runcmd(cmd, &data, 0);
		free_cmd(cmd);
		free(line);
	}
	free_all(&data);
	exit (data.exitcode);
}
