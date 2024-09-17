/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:19:50 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/17 14:19:23 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	free_exec(t_execcmd *ecmd)
{
	if (ecmd->args)
		free_array(ecmd->args);
	free(ecmd);
}

void	free_pipe(t_pipecmd *pcmd)
{
	free_cmd(pcmd->left);
	free_cmd(pcmd->right);
	free(pcmd);
}

void	free_redir(t_redircmd *rcmd)
{
	free_cmd(rcmd->cmd);
	free(rcmd->file);
	free(rcmd);
}

void	free_cmd(t_cmd *cmd)
{
	t_redircmd	*rcmd;
	t_listcmd	*lcmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		free_exec((t_execcmd *)cmd);
	else if (cmd->type == PIPE)
		free_pipe((t_pipecmd *)cmd);
	else if (cmd->type == REDIR)
		free_redir((t_redircmd *)cmd);
	else if (cmd->type == LIST)
	{
		lcmd = (t_listcmd *)cmd;
		free_cmd(lcmd->left);
		free_cmd(lcmd->right);
		free(lcmd);
	}
	else if (cmd->type == HEREDOC)
	{
		rcmd = (t_redircmd *)cmd;
		free_cmd(rcmd->cmd);
		free(rcmd);
	}
}
