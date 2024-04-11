/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:09:00 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/11 16:28:36 by hle-roi          ###   ########.fr       */
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

char	*handle_quotes(char *s, int i, int y)
{
	int		inquote;
	char	*cs;

	inquote = 0;
	if (!s)
		return (s);
	cs = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!cs)
		crash_handler("Expander \n");
	while (s[i])
	{
		i = is_inquote(s, &inquote, i);
		if (s[i] && (s[i] != '\"' || inquote == 2)
			&& (s[i] != '\'' || inquote == 1))
			cs[y++] = s[i++];
	}
	if (inquote != 0)
		crash_handler("Quote not allowed\n");
	free(s);
	return (cs);
}

char	*handle_env_var(char *s, char *es, char **env, int tok)
{
	int		inquote;
	char	*ps;
	char	*token;

	inquote = 0;
	ps = s;
	while (ps < es)
	{
		switch_inquote(ps, &inquote);
		if (*ps == '$' && !inquote)
		{
			ps++;
			tok = get_token(&ps, es, &token);
			break ;
		}
		ps++;
	}
	if (tok == 'a')
	{
		ps = get_env_var(token, env);
		if (ps)
			return (ps);
	}
	return (s);
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
			ecmd->args[i] = handle_quotes(ecmd->args[i], 0, 0);
			ecmd->args[i] = handle_env_var(ecmd->args[i],
					(ecmd->args[i] + ft_strlen(ecmd->args[i])), env, 0);
			i++;
		}
	}
	if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		rcmd->file = handle_quotes(rcmd->file, 0, 0);
	}
	return (cmd);
}
