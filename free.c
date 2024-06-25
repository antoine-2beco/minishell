/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:40:30 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/25 16:51:13 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	free_list(t_list *list)
{
	t_list	*temp_list;

	if (!list)
		return ;
	while (list)
	{
		temp_list = list->next;
		free (list);
		list = NULL;
		list = temp_list;
	}
	return ;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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
