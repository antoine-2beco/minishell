/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:11:17 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/10 13:32:34 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	rep;

	i = 0;
	rep = 0;
	while ((s1[i] || s2[i]))
	{
		rep = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (rep == 0)
			i++;
		else
			return (rep);
	}
	return (rep);
}

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return ((*s && ft_strchr(toks, *s)));
}

void	parseexec_error(t_execcmd *cmd, int argc)
{
	if (!cmd->args[argc])
		crash_handler("Malloc error\n");
	if (argc >= MAXARGS)
		crash_handler("too many args\n");
}

t_execcmd	*init_cmd(t_cmd *ret)
{
	t_execcmd	*cmd;

	cmd = (t_execcmd *)ret;
	cmd->args = malloc(sizeof(char *) * (MAXARGS + 1));
	if (!cmd->args)
		crash_handler("Malloc error\n");
	cmd->args[0] = malloc(sizeof(char *));
	if (!cmd->args[0])
		crash_handler("Malloc error\n");
	return (cmd);
}

t_cmd	*create_heredoc(t_cmd *cmd, char *file, char **env)
{
	char		*line;
	int			end[2];
	char		*delimiter;

	delimiter = handle_quotes(file, 0, 0);
	if (pipe(end) < 0)
		crash_handler("Pipe error\n");
	while (1)
	{
		ft_putstr_fd("heredoc>", STDERR_FILENO);
		line = readline(NULL);
		if (!ft_strchr(file, '\"') && !ft_strchr(file, '\"'))
			line = handle_env_var(line, (line + ft_strlen(line)), env, 0);
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, end[1]);
		ft_putstr_fd("\n", end[1]);
	}
	ft_putstr_fd("\0", end[1]);
	close(end[1]);
	cmd = redircmd(cmd, file, 0, end[0]);
	return (cmd);
}
