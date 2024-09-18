/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:09:00 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/18 17:07:25 by ade-beco         ###   ########.fr       */
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

int	check_quotes_utils(int *i, t_data *data, char *s, char *cs)
{
	char	*var;
	int		z;

	z = 0;
	var = 0;
	(i[0])++;
	if (s[i[0]] == '?')
	{
		var = ft_strdup(ft_itoa(data->exitcode));
		(i[0])++;
	}
	else if (!s[i[0]] || s[i[0]] == '\"' || s[i[0]] == ' ')
	{
		cs[(i[1])++] = '$';
		if (var)
			free(var);
		return (1);
	}
	else
		calcul_var(i, &var, s, data);
	if (!var)
		return (1);
	while (var[z])
		cs[(i[1])++] = var[z++];
	return (free(var), 0);
}

void	check_quotes(char *s, char *cs, int *inquote, t_data *data)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	while (s[i[0]])
	{
		i[0] = is_inquote(s, inquote, i[0]);
		if (s[i[0]] == '$' && *inquote != 2)
		{
			if (check_quotes_utils(i, data, s, cs))
				continue ;
		}
		else if (s[i[0]] == '\\' && !*inquote)
			(i[0])++;
		else if (s[i[0]] && (s[i[0]] != '\"' || *inquote == 2)
			&& (s[i[0]] != '\'' || *inquote == 1))
			cs[(i[1])++] = s[(i[0])++];
	}
}

char	*handle_quotes(char *s, t_data *data)
{
	int		inquote;
	char	*cs;
	int		len;

	len = 0;
	inquote = 0;
	if (!s)
		return (s);
	prompt_len(s, data, 0, &len);
	cs = ft_calloc(sizeof(char), len + 5);
	if (!cs)
		crash_handler("Expander \n");
	check_quotes(s, cs, &inquote, data);
	if (inquote != 0)
		crash_handler("Quote not allowed\n");
	free(s);
	if (!cs[0])
	{
		free(cs);
		return (NULL);
	}
	return (cs);
}
