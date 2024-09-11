/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:27:34 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/11 14:06:58 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

char	**s_get_args(char **ps, char *es, t_cmd **ret, t_data *data)
{
	char	*token;
	int		type;
	t_list	*tmp;
	t_list	*current;
	t_list	*list;

	list = NULL;
	current = NULL;
	tmp = NULL;
	while (!peek(ps, es, "|);"))
	{
		type = get_token(ps, es, &token);
		if (type == 0)
			break ;
		if (type != 'a')
			return (ft_printf("Synthax error\n", 2), NULL);
		get_args_norm(&list, &current, &tmp, token);
		*ret = s_parseredirs(*ret, ps, es, data);
	}
	tmp = ft_lstnew(0);
	if (current)
		current->next = tmp;
	else
		list = tmp;
	return (convert_list(list));
}

t_cmd	*s_parseredirs(t_cmd *cmd, char **ps, char *es, t_data *data)
{
	int		tok;
	char	*file;

	file = "1";
	tok = 0;
	(void)data;
	while (peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0);
		if (get_token(ps, es, &file) != 'a')
		{
			ft_printf("minishell: syntax error near unexpected token `%c\'\n", 2, tok);
			exit(2);
		}
		if (tok == '<')
			cmd = redircmd(cmd, file, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok == '-')
			cmd = redircmd(cmd, file, O_RDONLY, 0);
	}
	return (cmd);
}

t_cmd	*s_parseline(char **ps, char *es, t_data *data)
{
	t_cmd	*cmd;

	cmd = s_parsepipe(ps, es, data);
	if (peek(ps, es, ";"))
	{
		get_token(ps, es, 0);
		cmd = listcmd(cmd, s_parseline(ps, es, data));
	}
	return (cmd);
}

t_cmd	*s_parseblock(char **ps, char *es, t_data *data)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		crash_handler("parseblock\n");
	get_token(ps, es, 0);
	cmd = s_parseline(ps, es, data);
	if (!peek(ps, es, ")"))
		crash_handler("synthax - missing )\n");
	get_token(ps, es, 0);
	cmd = s_parseredirs(cmd, ps, es, data);
	return (cmd);
}

t_cmd	*s_parseexec(char **ps, char *es, t_data*data)
{
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (s_parseblock(ps, es, data));
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	ret = s_parseredirs(ret, ps, es, data);
	cmd->args = s_get_args(ps, es, &ret, data);
	if (!cmd->args[0])
		return (NULL);
	return (ret);
}

t_cmd	*s_parsepipe(char **ps, char *es, t_data *data)
{
	t_cmd	*cmd;

	cmd = s_parseexec(ps, es, data);
	if (peek(ps, es, "|"))
	{
		get_token(ps, es, 0);
		cmd = pipecmd(cmd, s_parsepipe(ps, es, data));
		if (!((t_pipecmd *)cmd)->left || !((t_pipecmd *)cmd)->right)
		{
			ft_printf("minishell: syntax error near unexpected token `|\'\n", 2);
			exit(2);
		}
	}
	return (cmd);
}

int	check_syntax(char **ps, char *es, t_data *data)
{
	int		pid;
	int		status;
	int		ret;

	pid = create_fork();
	ret = 1;
	if (!pid)
	{
		s_parseline(ps, es, data);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	if (ret)
		data->exitcode = ret;
	return (ret);
}
