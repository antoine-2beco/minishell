/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:33:52 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/17 10:51:52 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	expand_exec(t_execcmd *ecmd, t_data *data)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!ecmd->args)
		return ;
	while (ecmd->args[i])
	{
		ecmd->args[y] = handle_quotes(ecmd->args[i], data);
		if (ecmd->args[y][0])
			y++;
		i++;
	}
	while (ecmd->args[y])
		ecmd->args[y++] = 0;
}

void	expand_redir(t_redircmd *rcmd, t_data *data)
{
	rcmd->file = handle_quotes(rcmd->file, data);
	expand(rcmd->cmd, data);
}

t_cmd	*expand(t_cmd *cmd, t_data *data)
{
	t_pipecmd	*pcmd;
	t_listcmd	*lcmd;

	if (!cmd)
		return (NULL);
	if (cmd->type == EXEC)
		expand_exec((t_execcmd *)cmd, data);
	if (cmd->type == REDIR)
		expand_redir((t_redircmd *)cmd, data);
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
