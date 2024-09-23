/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:08:55 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/23 13:05:59 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, t_data *data)
{
	int		tok;
	char	*file;

	file = "1";
	tok = 0;
	while (peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if (get_token(ps, es, &file, 0) != 'a')
			crash_handler("missing file for redirection\n");
		if (tok == '<')
			cmd = redircmd(cmd, file, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok == '-')
		{
			cmd = create_heredoc(cmd, file, data);
			cmd->type = HEREDOC;
		}
	}
	return (cmd);
}

t_cmd	*parseline(char **ps, char *es, t_data *data)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es, data);
	if (peek(ps, es, ";"))
		;
	return (cmd);
}

t_cmd	*parseblock(char **ps, char *es, t_data *data)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		crash_handler("parseblock\n");
	get_token(ps, es, 0, 0);
	cmd = parseline(ps, es, data);
	if (!peek(ps, es, ")"))
		crash_handler("synthax - missing )\n");
	get_token(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es, data);
	return (cmd);
}

t_cmd	*parseexec(char **ps, char *es, t_data*data)
{
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es, data));
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	ret = parseredirs(ret, ps, es, data);
	cmd->args = get_args(ps, es, &ret, data);
	return (ret);
}

t_cmd	*parsepipe(char **ps, char *es, t_data *data)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es, data);
	if (peek(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es, data));
	}
	return (cmd);
}
