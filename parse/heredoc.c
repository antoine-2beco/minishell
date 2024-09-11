/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:00:29 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/11 13:48:05 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

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

	cs = ft_calloc(sizeof(char), prompt_len(s, data, 0, 0) + 1);
	if (!cs)
		crash_handler("Expander \n");
	check_var(s, cs, data, 0);
	free(s);
	return (cs);
}

void	read_heredoc(char *delimiter, t_data *data, int is_inquote, int *end)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", STDERR_FILENO);
		line = readline(NULL);
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
			break ;
		if (!is_inquote)
			line = handle_env_var(line, data);
		ft_putstr_fd(line, end[1]);
		ft_putstr_fd("\n", end[1]);
		free(line);
	}
	if (line)
		free(line);
}

t_cmd	*create_heredoc(t_cmd *cmd, char *file, t_data *data)
{
	int			end[2];
	char		*delimiter;
	int			is_inquote;
	int			i;

	i = -1;
	is_inquote = 0;
	while (file[++i])
	{
		if (file[i] == '\"' || file[i] == '\'')
			is_inquote = 1;
	}
	delimiter = handle_quotes(file, data);
	if (pipe(end) < 0)
		crash_handler("Pipe error\n");
	read_heredoc(delimiter, data, is_inquote, end);
	ft_putstr_fd("\0", end[1]);
	close(end[1]);
	cmd = redircmd(cmd, file, 0, end[0]);
	free(delimiter);
	cmd->type = HEREDOC;
	return (cmd);
}
