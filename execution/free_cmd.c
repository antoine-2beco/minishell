/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:17:38 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/21 16:22:30 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

void	free_cmd(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	t_listcmd	*lcmd;
	int			i;

	i = 0;
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
