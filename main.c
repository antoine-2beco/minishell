/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:13:09 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/20 13:25:11 by hle-roi          ###   ########.fr       */
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
	{
		ft_printf("leftovers: %s\n", 2, s);
		crash_handler("synthax\n");
	}
	return (cmd);
}

char	**cpy_env(char **pre_env)
{
	char	**env;
	int		i;

	i = 0;
	while (pre_env[i++])
		;
	env = malloc(i * sizeof(char *));
	if (!env)
		crash_handler("Error Malloc\n");
	i = 0;
	while (pre_env[i])
	{
		env[i] = ft_strdup(pre_env[i]);
		if (!env[i])
			crash_handler("Error Malloc\n");
		i++;
	}
	env[i] = 0;
	return (env);
}

void	init_data(t_data *data)
{
	data->i = 0;
	data->fd = 0;
	data->stdin_cpy = dup(STDIN_FILENO);
	data->stdout_cpy = dup(STDOUT_FILENO);
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
