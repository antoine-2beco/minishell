/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:09:00 by hle-roi           #+#    #+#             */
/*   Updated: 2024/08/07 17:33:48 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	is_inquote(char *s, int *inquote, int i)
{
	if (s[i] == '\"' && !*inquote)
	{
		*inquote = 1;
		i++;
	}
	if (s[i] == '\"' && *inquote == 1)
	{
		*inquote = 0;
		i++;
	}
	if (s[i] == '\'' && !*inquote)
	{
		*inquote = 2;
		i++;
	}
	if (s[i] == '\'' && *inquote == 2)
	{
		*inquote = 0;
		i++;
	}
	return (i);
}

char	*get_var(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i] && !ft_strchr(" \t\r\n\v\"\'", s[i]))
	{
		if (s[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		crash_handler("Malloc error\n");
	ft_strlcpy(ret, s, i);
	return (ret);
}

int	prompt_len(char *s, t_data *data, int i, int len)
{
	int		inquote;
	char	*var;
	int		a;

	inquote = 0;
	var = 0;
	while (s[i])
	{
		a = i;
		//i = is_inquote(s, &inquote, i);
		if (a != i)
			a = -1;
		if (s[i] == '$' && inquote != 2)
		{
			var = get_var(&s[++i]);
			i = i + ft_strlen(var);
			var = get_env_var(var, data);
			len = len + ft_strlen(var);
		}
		else if (a != -1)
		{
			len++;
			i++;
		}
	}
	if (var)
		free(var);
	return (len);
}

void	check_quotes(char *s, char *cs, int *inquote, t_data *data)
{
	char	*var;
	int		z;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (s[i])
	{
		z = 0;
		i = is_inquote(s, inquote, i);
		if (s[i] == '$' && *inquote != 2)
		{
			i++;
			if (!s[i] || s[i] == '\"' || s[i] == ' ')
			{
				cs[y++] = '$';
				continue ;
			}
			var = get_var(&s[i]);
			i = i + ft_strlen(var);
			var = get_env_var(var, data);
			if (!var)
				continue ;
			while (var[z])
				cs[y++] = var[z++];
			free(var);
		}
		else if (s[i] && (s[i] != '\"' || *inquote == 2)
			&& (s[i] != '\'' || *inquote == 1))
			cs[y++] = s[i++];
	}
}

char	*handle_quotes(char *s, t_data *data)
{
	int		inquote;
	char	*cs;

	inquote = 0;
	if (!s)
		return (s);
	cs = ft_calloc(sizeof(char), prompt_len(s, data, 0, 0) + 2);
	if (!cs)
		crash_handler("Expander \n");
	check_quotes(s, cs, &inquote, data);
	if (inquote != 0)
		crash_handler("Quote not allowed\n");
	free(s);
	return (cs);
}
