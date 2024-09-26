/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:00:29 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/26 16:55:49 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	g_signal;

void	check_var(char *s, char *cs, t_data *data, int y)
{
	int		z;
	int		i;
	char	*var;

	i = 0;
	while (s[i])
	{
		z = 0;
		if (s[i] == '$')
		{
			if (!s[++i])
				break ;
			var = get_var(&s[i]);
			i = i + ft_strlen(var);
			var = get_env_var(data->env, var);
			if (!var)
				break ;
			while (var[z])
				cs[y++] = var[z++];
			free(var);
		}
		else
			cs[y++] = s[i++];
	}
	cs[y] = 0;
}

char	*handle_env_var(char *s, t_data *data)
{
	char	*cs;
	int		len;

	len = 0;
	prompt_len(s, data, 0, &len);
	cs = ft_calloc(sizeof(char), len + 1);
	if (!cs)
		crash_handler("Expander \n");
	check_var(s, cs, data, 0);
	free(s);
	return (cs);
}

void	read_heredoc(char *delimiter, t_data *data, int is_inquote, int *end)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
			break ;
		if (!is_inquote)
			line = handle_env_var(line, data);
		ft_printf("%s\n", end[1], line);
		free(line);
	}
	if (line)
		free(line);
	exit(0);
}

void	create_heredoc_utils(int *end)
{
	ft_putstr_fd("\0", end[1]);
	close(end[1]);
	signal(SIGINT, sig_interrupt);
	if (g_signal == SIGINT)
	{
		close(end[0]);
		if (pipe(end) < 0)
			crash_handler("Pipe error\n");
		ft_putchar_fd('\0', end[1]);
		close(end[1]);
	}
}

t_cmd	*create_heredoc(t_cmd *cmd, char *file, t_data *data, int i)
{
	int			end[2];
	char		*delimiter;
	int			is_inquote;
	int			pid;

	g_signal = 0;
	is_inquote = 0;
	while (file[++i])
		if (file[i] == '\"' || file[i] == '\'')
			is_inquote = 1;
	delimiter = handle_quotes(file, data);
	if (pipe(end) < 0)
		crash_handler("Pipe error\n");
	signal(SIGINT, sig_interrupt_exec);
	pid = create_fork();
	if (!pid)
		read_heredoc(delimiter, data, is_inquote, end);
	waitpid(pid, NULL, 0);
	create_heredoc_utils(end);
	cmd = redircmd(cmd, file, 0, end[0]);
	cmd->type = HEREDOC;
	free(delimiter);
	return (cmd);
}
