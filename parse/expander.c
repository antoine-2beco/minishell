/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:09:00 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/17 13:46:23 by hle-roi          ###   ########.fr       */
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

int	prompt_len(char *s, char **env, int i, int len)
{
	int		inquote;
	char	*var;
	int		a;

	inquote = 0;
	while (s[i])
	{
		a = i;
		i = is_inquote(s, &inquote, i);
		if (a != i)
			a = -1;
		if (s[i] == '$' && inquote != 2)
		{
			var = get_var(&s[++i]);
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

char	*handle_quotes(char *s, int i, int y, t_data *data)
{
	int		inquote;
	char	*var;
	char	*cs;
	int		z;

	inquote = 0;
	if (!s)
		return (s);
	cs = ft_calloc(sizeof(char), prompt_len(s, data->env, 0, 0) + 1);
	if (!cs)
		crash_handler("Expander \n");
	while (s[i])
	{
		z = 0;
		i = is_inquote(s, &inquote, i);
		if (s[i] == '$' && inquote != 2)
		{
			i++;
			if (!s[i])
				break ;
			var = get_var(&s[i]);
			i = i + ft_strlen(var);
			var = get_env_var(var, data->env);
			if (!var)
				break ;
			while (var[z])
				cs[y++] = var[z++];
		}
		else if (s[i] && (s[i] != '\"' || inquote == 2)
			&& (s[i] != '\'' || inquote == 1))
			cs[y++] = s[i++];
	}
	if (inquote != 0)
		crash_handler("Quote not allowed\n");
	free(s);
	return (cs);
}

t_cmd	*expand(t_cmd *cmd, t_data *data)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;
	t_listcmd	*lcmd;
	int			i;

	i = 0;
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		while (ecmd->args[i])
		{
			ecmd->args[i] = handle_quotes(ecmd->args[i], 0, 0, data);
			i++;
		}
	}
	if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		rcmd->file = handle_quotes(rcmd->file, 0, 0, data);
		expand(rcmd->cmd, data);
	}
	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		expand(pcmd->left, data);
		expand(pcmd->right, data);
	}
	if (cmd->type == LIST)
	{
		lcmd = (t_listcmd *)cmd;
		expand(lcmd->left, data);
		expand(lcmd->right, data);
	}
	return (cmd);
}
