/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:11:17 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/03 11:03:54 by hle-roi          ###   ########.fr       */
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
