/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:11:17 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/05 14:48:12 by hle-roi          ###   ########.fr       */
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

int	get_token(char **ps, char *es, char **token)
{
	char	*s;
	int		ret;
	int		inquote;

	s = *ps;
	inquote = 0;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	if (token)
		*token = s;
	ret = *s;
	if (*s == 0)
		;
	else if (ft_strchr("|();", *s))
		s++;
	else if (*s == '<')
	{
		s++;
		if (*s == '<')
		{
			s++;
			ret = '-';
		}
	}
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			s++;
			ret = '+';
		}
	}
	else
	{
		ret = 'a';
		while (s < es && (!ft_strchr(" \t\r\n\v|();<>", *s) || inquote))
		{
			if ((*s == '\"') && inquote == 0)
				inquote = 1;
			else if ((*s == '\"') && inquote == 1)
				inquote = 0;
			else if ((*s == '\'') && inquote == 0)
				inquote = 2;
			else if ((*s == '\'') && inquote == 2)
				inquote = 0;
			s++;
		}
	}
	if (token)
		*token = ft_substr(*token, 0, s - *token);
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (ret);
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
			line = handle_env_var(line, (line + ft_strlen(line)), env);
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, end[1]);
	}
	ft_putstr_fd("\0", end[1]);
	close(end[1]);
	cmd = redircmd(cmd, file, 0, end[0]);
	return (cmd);
}
