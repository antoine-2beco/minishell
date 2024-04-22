/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:09:00 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/22 12:33:47 by hle-roi          ###   ########.fr       */
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
		i++;
	i++;
	ret = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(ret, s, i);
	return (ret);
}

int	prompt_len(char *s, char **env)
{
	int		inquote;
	int		i;
	int		len;
	char	*var;
	int		a;

	i = 0;
	len = 0;
	inquote = 0;
	while (s[i])
	{
		a = i;
		i = is_inquote(s, &inquote, i);
		if (a != i)
			a = -1;
		if (s[i] == '$' && inquote != 2)
		{
			i++;
			var = get_var(&s[i]);
			i = i + ft_strlen(var);
			var = get_env_var(var, env);
			len = len + ft_strlen(var);
		}
		else if (a != -1)
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*handle_quotes(char *s, int i, int y, char **env)
{
	int		inquote;
	char	*var;
	char	*cs;
	int		z;

	inquote = 0;
	if (!s)
		return (s);
	cs = ft_calloc(sizeof(char), prompt_len(s, env));
	if (!cs)
		crash_handler("Expander \n");
	while (s[i])
	{
		z = 0;
		i = is_inquote(s, &inquote, i);
		if (s[i] == '$' && inquote != 2)
		{
			i++;
			var = get_var(&s[i]);
			i = i + ft_strlen(var);
			var = get_env_var(var, env);
			while (var[z])
				cs[y++] = var[z++];
		}
		else if (s[i] && (s[i] != '\"' || inquote == 2) && (s[i] != '\'' || inquote == 1))
			cs[y++] = s[i++];
	}
	if (inquote != 0)
		crash_handler("Quote not allowed\n");
	free(s);
	return (cs);
}

t_cmd	*expand(t_cmd *cmd, char **env)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	int			i;

	i = 0;
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		while (ecmd->args[i])
		{
			ecmd->args[i] = handle_quotes(ecmd->args[i], 0, 0, env);
			i++;
		}
	}
	if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		rcmd->file = handle_quotes(rcmd->file, 0, 0, env);
	}
	return (cmd);
}
