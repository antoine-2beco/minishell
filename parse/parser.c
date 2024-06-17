/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:08:55 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/17 15:17:15 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, t_data *data)
{
	int		tok;
	char	*file;

	file = "1";
	while (peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0);
		if (get_token(ps, es, &file) != 'a')
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
	{
		get_token(ps, es, 0);
		cmd = listcmd(cmd, parseline(ps, es, data));
	}
	return (cmd);
}

t_cmd	*parseblock(char **ps, char *es, t_data *data)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		crash_handler("parseblock\n");
	get_token(ps, es, 0);
	cmd = parseline(ps, es, data);
	if (!peek(ps, es, ")"))
		crash_handler("synthax - missing )\n");
	get_token(ps, es, 0);
	cmd = parseredirs(cmd, ps, es, data);
	return (cmd);
}

t_cmd	*parseexec(char **ps, char *es, t_data *data, int argc)
{
	char		*token;
	int			type;
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es, data));
	ret = execcmd();
	cmd = init_cmd(ret);
	ret = parseredirs(ret, ps, es, data);
	while (!peek(ps, es, "|);"))
	{
		type = get_token(ps, es, &token);
		if (type == 0)
			break ;
		if (type != 'a')
		{
			ft_printf("Synthax error\n", 2);
			return (NULL);
		}
		cmd->args[argc++] = ft_strdup(token);
		if (!cmd->args[argc - 1])
			crash_handler("Error Malloc\n");
		free(token);
		cmd->args[argc] = malloc(sizeof(char *));
		if (!cmd->args[argc])
			crash_handler("Malloc error\n");
		if (argc >= MAXARGS)
			crash_handler("too many args\n");
		ret = parseredirs(ret, ps, es, data);
	}
	cmd->args[argc] = 0;
	return (ret);
}

t_cmd	*parsepipe(char **ps, char *es, t_data *data)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es, data, 0);
	if (peek(ps, es, "|"))
	{
		get_token(ps, es, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es, data));
	}
	return (cmd);
}
