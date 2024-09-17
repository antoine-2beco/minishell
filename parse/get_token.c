/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:22:30 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/17 14:15:00 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	get_ret(char **s, int *ret, char c)
{
	(*s)++;
	if (**s == '<' && c == '<')
	{
		(*s)++;
		*ret = '-';
	}
	if (**s == '>' && c == '>')
	{
		(*s)++;
		*ret = '+';
	}
}

void	get_exec_args(int *ret, char **s, char *es)
{
	int		inquote;

	inquote = 0;
	*ret = 'a';
	while (*s < es && (!ft_strchr(" \t\r\n\v|();<>", **s) || inquote))
	{
		if ((**s == '\"') && inquote == 0)
			inquote = 1;
		else if ((**s == '\"') && inquote == 1)
			inquote = 0;
		else if ((**s == '\'') && inquote == 0)
			inquote = 2;
		else if ((**s == '\'') && inquote == 2)
			inquote = 0;
		(*s)++;
	}
}

static char	*set_token(char *token, char *s)
{
	char	*temp;

	temp = NULL;
	if (ft_strlen(token) != 0)
	{
		temp = ft_substr(token, 0, s - token);
		if (!temp)
			crash_handler("Malloc error\n");
	}
	return (temp);
}

int	get_token(char **ps, char *es, char **token)
{
	char	*s;
	int		ret;
	char	*cpy;

	s = *ps;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	if (token)
		cpy = s;
	ret = *s;
	if (*s == 0)
		;
	else if (ft_strchr("|();", *s))
		s++;
	else if (*s == '<')
		get_ret(&s, &ret, *s);
	else if (*s == '>')
		get_ret(&s, &ret, *s);
	else
		get_exec_args(&ret, &s, es);
	if (token)
		*token = set_token(cpy, s);
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (ret);
}
