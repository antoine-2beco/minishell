/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:11:17 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/25 15:44:38 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return ((*s && ft_strchr(toks, *s)));
}

t_execcmd	*init_cmd(t_cmd *ret)
{
	t_execcmd	*cmd;

	cmd = (t_execcmd *)ret;
	cmd->args = malloc(sizeof(char *) * (MAXARGS));
	if (!cmd->args)
		crash_handler("Malloc error\n");
	return (cmd);
}

char	*handle_env_var(char *s, t_data *data)
{
	int		i;
	int		z;
	int		y;
	char	*var;
	char	*cs;

	cs = ft_calloc(sizeof(char), prompt_len(s, data, 0, 0) + 1);
	if (!cs)
		crash_handler("Expander \n");
	i = 0;
	y = 0;
	while (s[i])
	{
		z = 0;
		if (s[i] == '$')
		{
			i++;
			if (!s[i])
				break ;
			var = get_var(&s[i]);
			i = i + ft_strlen(var);
			var = get_env_var(var, data);
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
	if (var)
		free(var);
	free(s);
	return (cs);
}

t_cmd	*create_heredoc(t_cmd *cmd, char *file, t_data *data)
{
	char		*line;
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
	delimiter = handle_quotes(file, 0, 0, data);
	if (pipe(end) < 0)
		crash_handler("Pipe error\n");
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
	ft_putstr_fd("\0", end[1]);
	close(end[1]);
	cmd = redircmd(cmd, file, 0, end[0]);
	free(delimiter);
	return (cmd);
}
