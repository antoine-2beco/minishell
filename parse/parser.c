/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:08:55 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/11 10:12:49 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, char **env)
{
	int		tok;
	char	*file;

	file = "1";
	while (peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0);
		if (get_token(ps, es, &file) != 'a')
			crash_handler("missing file for redirection");
		if (tok == '<')
			cmd = redircmd(cmd, file, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok == '-')
		{
			cmd = create_heredoc(cmd, file, env);
			cmd->type = HEREDOC;
		}
	}
	return (cmd);
}

t_cmd	*parseline(char **ps, char *es, char **env)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es, env);
	if (peek(ps, es, ";"))
	{
		get_token(ps, es, 0);
		cmd = listcmd(cmd, parseline(ps, es, env));
	}
	return (cmd);
}

t_cmd	*parseblock(char **ps, char *es, char **env)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		crash_handler("parseblock");
	get_token(ps, es, 0);
	cmd = parseline(ps, es, env);
	if (!peek(ps, es, ")"))
		crash_handler("synthax - missing )");
	get_token(ps, es, 0);
	cmd = parseredirs(cmd, ps, es, env);
	return (cmd);
}

t_cmd	*parseexec(char **ps, char *es, char **env, int argc)
{
	char		*token;
	int			type;
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es, env));
	ret = execcmd();
	cmd = init_cmd(ret);
	ret = parseredirs(ret, ps, es, env);
	while (!peek(ps, es, "|);"))
	{
		type = get_token(ps, es, &token);
		if (type == 0)
			break ;
		if (type != 'a')
			crash_handler("synthax\n");
		cmd->args[argc++] = token;
		cmd->args[argc] = malloc(sizeof(char *));
		parseexec_error(cmd, argc);
		ret = parseredirs(ret, ps, es, env);
	}
	cmd->args[argc] = 0;
	return (ret);
}

t_cmd	*parsepipe(char **ps, char *es, char **env)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es, env, 0);
	if (peek(ps, es, "|"))
	{
		get_token(ps, es, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es, env));
	}
	return (cmd);
}
