/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:17:38 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/23 16:28:37 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	free_cmd(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	t_listcmd	*lcmd;

	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		free_array(ecmd->args);
		free(ecmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		free_cmd(pcmd->left);
		free_cmd(pcmd->right);
		free(pcmd);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		free_cmd(rcmd->cmd);
		free(rcmd->file);
		free(rcmd);
	}
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
