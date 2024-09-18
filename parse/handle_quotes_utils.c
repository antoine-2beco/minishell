/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:41:37 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/18 10:12:37 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

char	*get_var(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i] && !ft_strchr(" \t\r\n\v\"\'", s[i]))
	{
		if (s[i] == '?')
			break ;
		i++;
	}
	i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		crash_handler("Malloc error\n");
	ft_strlcpy(ret, s, i);
	return (ret);
}

void	calcul_var(int *i, char **var, char *s, t_data *data)
{
	char	*tmp;

	tmp = get_var(&s[*i]);
	*i = *i + ft_strlen(tmp);
	*var = get_env_var(data->env, tmp);
	free(tmp);
}

void	prompt_len(char *s, t_data *data, int i, int *len)
{
	int		inquote;
	char	*var;
	int		a;

	inquote = 0;
	var = 0;
	while (s[i])
	{
		a = i;
		i = is_inquote(s, &inquote, i);
		if (a != i)
			a = -1;
		if (s[i] == '$' && inquote != 2)
		{
			i++;
			calcul_var(&i, &var, s, data);
			*len = *len + ft_strlen(var);
			free(var);
		}
		else if (a != -1)
		{
			(*len)++;
			i++;
		}
	}
}
