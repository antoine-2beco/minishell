/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:08:55 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/03 10:50:33 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
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
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT, 1);
		else if (tok == '-')
		{
			cmd = redircmd(cmd, file, 0, 0);
			cmd->type = HEREDOC;
		}
	}
	return (cmd);
}

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es);
	if (peek(ps, es, ";"))
	{
		get_token(ps, es, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return (cmd);
}

t_cmd	*parseblock(char **ps, char *es)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		crash_handler("parseblock");
	get_token(ps, es, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		crash_handler("synthax - missing )");
	get_token(ps, es, 0);
	cmd = parseredirs(cmd, ps, es);
	return (cmd);
}

t_cmd	*parseexec(char **ps, char *es)
{
	char		*token;
	int			type;
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	token = "1";
	argc = 0;
	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	cmd->args = malloc(sizeof(char *) * MAXARGS);
	if (!cmd->args)
		return (NULL);
	cmd->args[argc] = malloc(sizeof(char *));
	if (!cmd->args[argc])
		return (NULL);
	ret = parseredirs(ret, ps, es);
	while (!peek(ps, es, "|);"))
	{
		type = get_token(ps, es, &token);
		if (type == 0)
			break ;
		if (type != 'a')
			crash_handler("synthax\n");
		cmd->args[argc++] = token;
		cmd->args[argc] = malloc(sizeof(char *));
		if (!cmd->args[argc])
			return (NULL);
		if (argc >= MAXARGS)
			crash_handler("too many args\n");
		ret = parseredirs(ret, ps, es);
	}
	cmd->args[argc] = 0;
	return (ret);
}

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		get_token(ps, es, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}
